// Fill out your copyright notice in the Description page of Project Settings.


#include "ControlledSoul.h"

#include "CheckpointBasedGamemode.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Engine/LocalPlayer.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AControlledSoul::AControlledSoul()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bHasJumped = false;
	bHasJumpedTwice = false;
	bIsGrounded = true;

	coolDownBetweenJumps=0.25f;
	currentCooldownTime=0.26f;
}

// Called when the game starts or when spawned
void AControlledSoul::BeginPlay()
{
	Super::BeginPlay();
	RootPhysicsComponent = Cast<UPrimitiveComponent>(this->GetRootComponent());
	RootPhysicsComponent->OnComponentHit.AddDynamic(this,&AControlledSoul::OnPlayerCollision);
	
	AController* thisPawnController = GetController(); // gets controller controlling this pawn
	APlayerController* currentController = Cast<APlayerController>(thisPawnController);// cast down to player controller
	
	this->SetupMappingContext(currentController);
	this->SetupBindActions(currentController);


	ACheckpointBasedGamemode* gamemode = Cast<ACheckpointBasedGamemode>(UGameplayStatics::GetGameMode(GetWorld()));
	gamemode->RespawnTransform = new FTransform();
	gamemode->RespawnTransform->SetLocation(this->GetActorLocation());
	
}


void AControlledSoul::SetupMappingContext(APlayerController* currentController)
{
	
	ULocalPlayer* localPlayer = currentController->GetLocalPlayer();// gets local player reference to get input subsystem
	UEnhancedInputLocalPlayerSubsystem* InputSystem = localPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();// Get input susbsystem

	InputSystem->AddMappingContext(controlledSoulMappingContext,0);// set mapping for the subsystem
}

void AControlledSoul::SetupBindActions(APlayerController* currentController)
{
	enhancedInputComponent = Cast<UEnhancedInputComponent>(currentController->InputComponent);
	enhancedInputComponent->BindAction(horizontalMovementAction,ETriggerEvent::Triggered,this,&AControlledSoul::MoveHorizontally);
	enhancedInputComponent->BindAction(JumpAction,ETriggerEvent::Started,this,&AControlledSoul::CustomJumpImpulse);
	//enhancedInputComponent->BindAction(JumpAction,ETriggerEvent::Completed,this,&AControlledSoul::StopJumping);


}

void AControlledSoul::MoveHorizontally(const FInputActionValue& value)
{
	float horizontalMovementDirection = value.Get<float>();


	// Store for animation
	if (horizontalMovementDirection != 0.f)
	{
		LastInputDirection = horizontalMovementDirection;
	}

	
	float deltaTime = UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
	FVector currentLocation = this->GetActorLocation();
	FVector newLocation = FVector(currentLocation.X,currentLocation.Y + horizontalMovementDirection*horizontalMoveSpeed*deltaTime,currentLocation.Z);
	this->SetActorLocation(newLocation);
	

	
}

void AControlledSoul::RaycastForGroundChecking()
{
	FHitResult groundHitResult;
	
	FVector downVector = this->GetActorUpVector()*-1;
	FVector endRaycastPoint = this->GetActorLocation() + downVector*raycastLength;

	FCollisionQueryParams queryParams;
	queryParams.AddIgnoredActor(this);

	this->bIsGrounded = GetWorld()->LineTraceSingleByChannel(
	   groundHitResult,
	   this->GetActorLocation(),
	   endRaycastPoint,
	   ECC_WorldDynamic,
	   queryParams
   );


	if (bIsGrounded)
	{
		UE_LOG(LogTemp, Warning, TEXT("acertou no objeto: %s"),*groundHitResult.GetActor()->GetName());
		bHasJumped = false;
		bHasJumpedTwice = false;
		currentCooldownTime = 0.0f;

		RootPhysicsComponent->SetPhysicsLinearVelocity(FVector(0,0,0));
	}
		
	
	DrawDebugLine(GetWorld(), this->GetActorLocation(),  endRaycastPoint, bIsGrounded ? FColor::Green : FColor::Red, false, 2.f, 0, 2.f);

}


void AControlledSoul::OnPlayerCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Display, TEXT("bateu em alguma merda"));

	RaycastForGroundChecking();

		
}

// Called every frame
void AControlledSoul::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	
	FVector currentVelocity =  RootPhysicsComponent->GetPhysicsLinearVelocity();
	float currentVelocityMagnitude =currentVelocity.Size();
	currentVelocity.Normalize();
	//UE_LOG(LogTemp, Display, TEXT("CURRENT LINEAR VELOCITY: %f"), currentVelocityMagnitude);

	//check if velocity too fast clamp it
	if (currentVelocityMagnitude > maxSpeedForClamping)
	{
		RootPhysicsComponent->SetPhysicsLinearVelocity(currentVelocity*maxSpeedForClamping);
		UE_LOG(LogTemp, Display, TEXT("GOING TOO FAST,WE CLAMP IT"));

	}

	
	if (bHasJumped)
	{
		currentCooldownTime += DeltaTime;
	}

	bool hasPassedJumpCooldownTime = currentCooldownTime >= coolDownBetweenJumps;
	if (hasPassedJumpCooldownTime)
	{
		RaycastForGroundChecking();
	}
	

}


// Called to bind functionality to input
void AControlledSoul::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void AControlledSoul::OnPushed_Implementation(FVector PushDirection, float Force)
{
	UE_LOG(LogTemp, Display, TEXT("ControlledSoul pushed! Direction: %s, Force: %f"), 
	*PushDirection.ToString(), Force);


	//Reset velocity
	float currentVelocityMagnitude = RootPhysicsComponent->GetPhysicsLinearVelocity().Size();
	RootPhysicsComponent->SetPhysicsLinearVelocity(PushDirection*currentVelocityMagnitude);

	
	// Apply push to velocity
	FVector PushVelocity = PushDirection * Force;
	// For 2.5D, you might want to only push in Y-Z
	PushVelocity.X = 0.0f;
	DrawDebugLine(
		GetWorld(),
		this->GetActorLocation(),
		this->GetActorLocation() + PushDirection,
		FColor::Blue,
		false,
		5,
		0,
		3.0f
	);
	RootPhysicsComponent->AddImpulse(PushVelocity);
}

void AControlledSoul::CustomJumpImpulse(const FInputActionValue& value)
{
	
	bool CanSecondJump = bHasJumped && currentCooldownTime >= coolDownBetweenJumps;
	
	if (bHasJumpedTwice || (!CanSecondJump & bHasJumped))  return; // dont jump if already jumped twice or if on cooldown

	FVector currentVelocity = RootPhysicsComponent->GetPhysicsLinearVelocity();
	RootPhysicsComponent->SetPhysicsLinearVelocity(FVector(currentVelocity.X, currentVelocity.Y, 0));
	RootPhysicsComponent->AddImpulse(this->GetActorUpVector()*jumpImpulseForce);

	if (bHasJumped) bHasJumpedTwice = true;
	bHasJumped = true;
	
	bIsGrounded = false;
	
}

void AControlledSoul::KillPlayer()
{
	ACheckpointBasedGamemode* gamemode = Cast<ACheckpointBasedGamemode> (UGameplayStatics::GetGameMode(GetWorld()));
	gamemode->RespawnPlayerControlledSoul(Cast<APlayerController>(this->GetController()),this);
	
}





// Fill out your copyright notice in the Description page of Project Settings.


#include "ControlledSoul.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Engine/LocalPlayer.h"

// Sets default values
AControlledSoul::AControlledSoul()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AControlledSoul::BeginPlay()
{
	Super::BeginPlay();
	RootPhysicsComponent = Cast<UPrimitiveComponent>(this->GetRootComponent());
	
	camera = Cast<USceneComponent>(this->GetComponentByClass<UCameraComponent>());
	camera->AddLocalOffset(cameraOffset);
	
	
	AController* thisPawnController = GetController(); // gets controller controlling this pawn
	APlayerController* currentController = Cast<APlayerController>(thisPawnController);// cast down to player controller
	
	this->SetupMappingContext(currentController);
	this->SetupBindActions(currentController);
	
	
	
	//enhancedInputComponent->BindAction();
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

	FVector currentLocation = this->GetActorLocation();
	FVector newLocation = FVector(currentLocation.X,currentLocation.Y + horizontalMovementDirection,currentLocation.Z);
	this->SetActorLocation(newLocation);
	

	
}


// Called every frame
void AControlledSoul::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
	UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(this->GetRootComponent());
	PrimitiveComponent->AddImpulse(this->GetActorUpVector()*jumpImpulseForce);
	
}


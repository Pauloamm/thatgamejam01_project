// Fill out your copyright notice in the Description page of Project Settings.


#include "Star.h"

#include "EnhancedInputComponent.h"
#include "MaterialHLSLTree.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AStar::AStar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mousePosition = new FVector();
}

// Called when the game starts or when spawned
void AStar::BeginPlay()
{
	Super::BeginPlay();
	playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	enhancedInputComponent = (UEnhancedInputComponent*)playerController->InputComponent;

	UE_LOG(LogTemp, Display, TEXT("IS ENHANCED INPUT NULL??: %hhd"), (enhancedInputComponent==NULL));

	
	//enhancedInputComponent->BindAction(moveMouseAction,ETriggerEvent::Triggered, this, &AStar::ChangeStarPosition);

	currentCenterActor = GetAttachParentActor();
	// This works! Your original approach was correct
	currentCenterActor = GetAttachParentActor();
    
	if (currentCenterActor)
	{
		UE_LOG(LogTemp, Display, TEXT("Star center set to: %s"), *currentCenterActor->GetName());
	}
}

void AStar::ChangeStarPosition(float DeltaTime)
{
	FVector currentCenterActorLocation = currentCenterActor->GetActorLocation();

	
	FVector2D mouseInputValue;
	// mouseInputValue = Value.Get<FVector2D>();
	FVector currentPosition = this->GetActorLocation();
	
	playerController->GetMousePosition(mouseInputValue.X, mouseInputValue.Y);
	UE_LOG(LogTemp, Display, TEXT("MOUSE POSITION IN SCREEN: %s"), *mouseInputValue.ToString());

	FVector worldLocation, worldDirection;
	playerController->DeprojectScreenPositionToWorld(mouseInputValue.X, mouseInputValue.Y, worldLocation, worldDirection);

	// Ray-plane intersection
	// We want to find where the ray hits the plane at X = center.X
	// Ray equation: Point = worldLocation + worldDirection * t
	// Plane equation: X = center.X
	// Solve for t: worldLocation.X + worldDirection.X * t = center.X
    
	float t = (currentCenterActorLocation.X - worldLocation.X) / worldDirection.X;
    
	// Calculate the intersection point
	FVector intersectionPoint = worldLocation + (worldDirection * t);
    
	// Now intersectionPoint.Y and intersectionPoint.Z are the actual world coordinates
	FVector actualWorldLocation = FVector(currentCenterActorLocation.X, intersectionPoint.Y, intersectionPoint.Z);
    




	
	UE_LOG(LogTemp, Display, TEXT("CONVERTED TO WORLD POSITION: %s"), *worldLocation.ToString());


	FVector desiredPosition = FVector(
	   currentCenterActorLocation.X, // Keep same X depth as center
	   actualWorldLocation.Y, // Use mouse world Y
	   actualWorldLocation.Z  // Use mouse world Z
   );
	UE_LOG(LogTemp, Display, TEXT("DESIRED POSITION: %s"), *worldLocation.ToString());

	FVector directionToMouse = desiredPosition - currentCenterActorLocation;

	//If mouse is further than radius set max distance
	float distanceToMove = directionToMouse.Size(); 
	if (directionToMouse.Size() > maxDistanceFromParent) distanceToMove = maxDistanceFromParent;
	
	directionToMouse = directionToMouse.GetSafeNormal() * distanceToMove;
	
		FVector finalPosition = FVector(
			currentCenterActorLocation.X,
			currentCenterActorLocation.Y + directionToMouse.Y,
			currentCenterActorLocation.Z + directionToMouse.Z
		);
	
    FVector thisFrameMoveDirection = finalPosition-GetActorLocation();
	
	if (thisFrameMoveDirection.Size() <arrivedRadius) return;// if clsoe enough dont process anything else, no need to move this frame
	
	thisFrameMoveDirection.Normalize();
	thisFrameMoveDirection = thisFrameMoveDirection*DeltaTime*starSpeed;
	SetActorLocation(GetActorLocation() + thisFrameMoveDirection);
	
}


// Called every frame
void AStar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ChangeStarPosition(DeltaTime);
}


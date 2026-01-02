// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterFlipbookController.h"

#include "SWarningOrErrorBox.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"

// Sets default values for this component's properties
UCharacterFlipbookController::UCharacterFlipbookController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	directionToChangeFlipbook = FlipbookDirection::RIGHT;

	// ...
}


// Called when the game starts
void UCharacterFlipbookController::BeginPlay()
{
	Super::BeginPlay();

	owner = GetOwner();
	flipbook = Cast<UPaperFlipbookComponent>(owner->GetComponentByClass(UPaperFlipbookComponent::StaticClass()));
	lastYPos = GetOwner()->GetActorLocation().Y;
	OriginalXScale = flipbook->GetRelativeScale3D().X;

	flipbook-> SetFlipbook(walkingAnimation);
	


}


// Called every frame
void UCharacterFlipbookController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	FlipbookDirection currentDirectionForFlipbook = GetFlipbookDirectionToChange();

	FVector currentFlipbookScale = flipbook->GetComponentScale();	

	switch (currentDirectionForFlipbook)
	{
		case FlipbookDirection::RIGHT:
		flipbook->SetWorldScale3D(FVector(OriginalXScale,currentFlipbookScale.Y , currentFlipbookScale.Z)); // positive
		break;
		
		case FlipbookDirection::LEFT:
		flipbook->SetWorldScale3D(FVector(OriginalXScale * -1,currentFlipbookScale.Y, currentFlipbookScale.Z)); // negative
		break;
		
		default:
		flipbook->SetWorldScale3D(FVector(currentFlipbookScale.X, currentFlipbookScale.Y, currentFlipbookScale.Z)); // negative
		break;
	}

	float currentZVelocity = owner->GetVelocity().Z;
	if (currentZVelocity > FLT_EPSILON || currentZVelocity < -FLT_EPSILON) // is in air
		flipbook->SetFlipbook(floatingAnimation);
	else
		flipbook->SetFlipbook(walkingAnimation);

		
	
}

UCharacterFlipbookController::FlipbookDirection UCharacterFlipbookController::GetFlipbookDirectionToChange()
{
	FlipbookDirection newDirection;

	
	currentYPos = GetOwner()->GetActorLocation().Y;

	if (currentYPos == lastYPos)
		newDirection = FlipbookDirection::SAME;
	else if (currentYPos > lastYPos)
		newDirection = FlipbookDirection::RIGHT;

	else newDirection = FlipbookDirection::LEFT;

	


	lastYPos = currentYPos;
	return newDirection;
	
}





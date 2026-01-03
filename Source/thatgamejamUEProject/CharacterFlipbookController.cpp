// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterFlipbookController.h"


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

	owner = Cast<AControlledSoul>( GetOwner());
	flipbook = Cast<UPaperFlipbookComponent>(owner->GetComponentByClass(UPaperFlipbookComponent::StaticClass()));
	lastYPos = GetOwner()->GetActorLocation().Y;
	OriginalXScale = flipbook->GetRelativeScale3D().X;

	flipbook-> SetFlipbook(walkingAnimation);
	


}


// Called every frame
void UCharacterFlipbookController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
		float InputDir = owner->GetLastInputDirection();
        
		FVector currentFlipbookScale = flipbook->GetComponentScale();
        
		if (InputDir > 0.f)
		{
			flipbook->SetWorldScale3D(FVector(OriginalXScale, currentFlipbookScale.Y, currentFlipbookScale.Z));
		}
		else if (InputDir < 0.f)
		{
			flipbook->SetWorldScale3D(FVector(OriginalXScale * -1, currentFlipbookScale.Y, currentFlipbookScale.Z));
		}
		// If InputDir == 0, keep current facing
	

	// Animation state based on Z velocity
	float currentZVelocity = owner->GetVelocity().Z;
	if (currentZVelocity > FLT_EPSILON || currentZVelocity < -FLT_EPSILON)
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





// Fill out your copyright notice in the Description page of Project Settings.


#include "StarFlipbookController.h"

// Sets default values for this component's properties
UStarFlipbookController::UStarFlipbookController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	directionToChangeFlipbook = FlipbookDirection::RIGHT;

	// ...
}


// Called when the game starts
void UStarFlipbookController::BeginPlay()
{
	Super::BeginPlay();
	
	owner = GetOwner();
	flipbook = Cast<UPaperFlipbookComponent>(owner->GetComponentByClass(UPaperFlipbookComponent::StaticClass()));
	flipbook->SetFlipbook(sideAnimation);

	lastZPos = owner->GetActorLocation().Z - owner->GetParentActor()->GetActorLocation().Z;
	OriginalXScale = flipbook->GetRelativeScale3D().X;

	// ...
	
}


// Called every frame
void UStarFlipbookController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	FlipbookDirection currentDirectionForFlipbook = GetFlipbookDirectionToChange();

	FVector currentFlipbookScale = flipbook->GetComponentScale();	

	switch (currentDirectionForFlipbook)
	{
	case FlipbookDirection::RIGHT:
		flipbook->SetWorldScale3D(FVector(OriginalXScale * -1,currentFlipbookScale.Y , currentFlipbookScale.Z)); // positive

		break;
		
	case FlipbookDirection::LEFT:
		flipbook->SetWorldScale3D(FVector(OriginalXScale,currentFlipbookScale.Y, currentFlipbookScale.Z)); // negative
		break;
		
	default:
		flipbook->SetWorldScale3D(FVector(currentFlipbookScale.X, currentFlipbookScale.Y, currentFlipbookScale.Z)); // negative
		break;
	}


	
	ChangeFlipbookAnimationsAccordingToUpDownDirection();
}

void UStarFlipbookController::ChangeFlipbookAnimationsAccordingToUpDownDirection()
{
	currentZPos = owner->GetActorLocation().Z - owner->GetParentActor()->GetActorLocation().Z;



	if (fabs(currentZPos - lastZPos) < 2.5f)
	{
		//flipbook->SetFlipbook(sideAnimation);
		//UE_LOG(LogTemp, Warning, TEXT("METEU ANIMAÇAO ESTRELA DE LADO"));


	}
	else if (currentZPos > lastZPos)
	{
		flipbook->SetFlipbook(upAnimation);
		//UE_LOG(LogTemp, Warning, TEXT("METEU ANIMAÇAO ESTRELA PARA CIMA"));


	}
	else
	{

		flipbook->SetFlipbook(downAnimation);
		//UE_LOG(LogTemp, Warning, TEXT("METEU ANIMAÇAO ESTRELA PARA BAIXO"));

	}

	lastZPos = currentZPos;
}

UStarFlipbookController::FlipbookDirection UStarFlipbookController::GetFlipbookDirectionToChange()
{
	FlipbookDirection newDirection;

	
	currentYPos = GetOwner()->GetActorLocation().Y - owner->GetParentActor()->GetActorLocation().Y;
	//UE_LOG(LogTemp, Warning, TEXT("CURRENT RELATIVE STAR Y : %f, last relative star Y: %f "), currentYPos, lastYPos);

	if (fabs(currentYPos - lastYPos) <  2.5f )
		newDirection = FlipbookDirection::SAME;
	
	else if (currentYPos > lastYPos)
		newDirection = FlipbookDirection::RIGHT;
	else newDirection = FlipbookDirection::LEFT;

	


	lastYPos = currentYPos;
	return newDirection;
}


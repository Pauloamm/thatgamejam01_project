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

	
	enhancedInputComponent->BindAction(moveMouseAction,ETriggerEvent::Triggered, this, &AStar::ChangeStarPosition);
}

void AStar::ChangeStarPosition(const FInputActionValue& Value)
{
	
	FVector2D mouseInputValeu = Value.Get<FVector2D>();
	FVector currentPosition = this->GetActorLocation();
	
	//playerController->GetMousePosition(mouseInputValeu.X, mouseInputValeu.Y);
	UE_LOG(LogTemp, Display, TEXT("The vector value is: %s"), *mouseInputValeu.ToString());

	
	
	FVector newPosition = FVector(currentPosition.X,
		currentPosition.Y + (mouseInputValeu.X*starVelocity),
		currentPosition.Z -(mouseInputValeu.Y*starVelocity));
	

	SetActorLocation(newPosition);
}


// Called every frame
void AStar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


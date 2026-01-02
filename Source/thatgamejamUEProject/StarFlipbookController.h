// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PaperFlipbookComponent.h"

#include "StarFlipbookController.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THATGAMEJAMUEPROJECT_API UStarFlipbookController : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStarFlipbookController();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = paper)
	UPaperFlipbookComponent* flipbook;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = paper)
	UPaperFlipbook* downAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = paper)
	UPaperFlipbook* upAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = paper)
	UPaperFlipbook* sideAnimation;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	AActor* owner;
	float lastZPos;
	float currentZPos;
	
	
	void ChangeFlipbookAnimationsAccordingToUpDownDirection();

	//Flipping left right
	enum class FlipbookDirection
	{
		SAME,
		RIGHT,
		LEFT
	} directionToChangeFlipbook;
	
	float OriginalXScale;
	float lastYPos;
	float currentYPos;

	FlipbookDirection GetFlipbookDirectionToChange();
};

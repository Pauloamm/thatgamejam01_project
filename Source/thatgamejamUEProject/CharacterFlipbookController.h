// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PaperFlipbookComponent.h"
#include "ControlledSoul.h"


#include "CharacterFlipbookController.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THATGAMEJAMUEPROJECT_API UCharacterFlipbookController : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterFlipbookController();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UPaperFlipbookComponent* flipbook;
	

	// UP/DOWN animation changing
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = paper)
	UPaperFlipbook* walkingAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = paper)
	UPaperFlipbook* floatingAnimation;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	//Flipping left right
	enum class FlipbookDirection
	{
		SAME,
		RIGHT,
		LEFT
	} directionToChangeFlipbook;
	
	AControlledSoul* owner;
	float OriginalXScale;
	float lastYPos;
	float currentYPos;

	FlipbookDirection GetFlipbookDirectionToChange();


	
};

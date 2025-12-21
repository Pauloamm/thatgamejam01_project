// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "GameFramework/Actor.h"
#include "Star.generated.h"

UCLASS()
class THATGAMEJAMUEPROJECT_API AStar : public AActor
{
	GENERATED_BODY()



public:	
	// Sets default values for this actor's properties
	AStar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual void ChangeStarPosition(const FInputActionValue& value);

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	float starVelocity;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	APlayerController* playerController;

	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category="Input")
	UEnhancedInputComponent* enhancedInputComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category="Input")
	UInputAction* moveMouseAction;


	
	FVector* mousePosition;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

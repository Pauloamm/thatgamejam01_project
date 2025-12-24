// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAbility.h"
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
	virtual void ChangeStarPosition(float DeltaTime);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Abilities")
	TArray<UBaseAbility*> abilities;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	APlayerController* playerController;

	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category="Input")
	UEnhancedInputComponent* enhancedInputComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category="Input")
	UInputAction* moveMouseAction;

	
	UPROPERTY(VisibleAnywhere, Category="Parent")
	AActor* currentCenterActor;
	UPROPERTY(EditAnywhere, Category="Star Max Radius")
	float maxDistanceFromParent;
	UPROPERTY(EditAnywhere, Category="Star Speed")
	float starSpeed;
	UPROPERTY(EditAnywhere, Category="Star Speed")
	float arrivedRadius;

	FVector* mousePosition;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category="Star")
	void LockInPlace(bool bLock);
private:
	
	
	
	bool bIsLockedInPlace = false;
	FVector LockedWorldLocation;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAbility.h"
#include "PushAroundAbility.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Abilities), meta=(BlueprintSpawnableComponent))
class THATGAMEJAMUEPROJECT_API UPushAroundAbility : public UBaseAbility
{
	GENERATED_BODY()

	public:
	UPushAroundAbility();


	protected:
	virtual void ActivateAbility_Implementation(const FInputActionValue& value) override;
	virtual void DeactivateAbility_Implementation() override;

private:
	UPROPERTY(EditAnywhere)
	float PushRadius;

	UPROPERTY(EditAnywhere)
	float PushForce;

	void PushActor(AActor* actorToPush);
};

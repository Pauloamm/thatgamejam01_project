// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAbility.h"
#include "GrapplingHookAbility.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Abilities), meta=(BlueprintSpawnableComponent))
class THATGAMEJAMUEPROJECT_API UGrapplingHookAbility : public UBaseAbility
{
	GENERATED_BODY()

public:
	UGrapplingHookAbility();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void ActivateAbility_Implementation(const FInputActionValue& value) override;
	virtual void DeactivateAbility_Implementation() override;


private:
	bool bIsPushingTowardsStar;

	UPROPERTY(EditAnywhere)
	float deadZoneRadiusAroundStar;
	
	UPROPERTY(EditAnywhere)
	float pullForce;
public:
	 virtual void BindInput_Implementation(UEnhancedInputComponent* InputComponent) override;
};

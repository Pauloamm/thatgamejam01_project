// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AbilityInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAbilityInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THATGAMEJAMUEPROJECT_API IAbilityInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Activation")
	void ActivateAbility(const FInputActionValue& value);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Activation")
	void DeactivateAbility();

	// Getters - call only
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Activation")
	bool CanActivate() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Name")
	FName GetAbilityName() const;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Cooldown")
	float GetCooldown() const;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Cooldown")
	bool IsOnCooldown() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Ability")
	void BindInput(UEnhancedInputComponent* InputComponent);
};

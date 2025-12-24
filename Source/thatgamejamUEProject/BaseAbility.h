// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityInterface.h"
#include "InputAction.h"
#include "Components/ActorComponent.h"
#include "BaseAbility.generated.h"


UCLASS( ClassGroup=(Custom), EditInlineNew, meta=(BlueprintSpawnableComponent) )
class THATGAMEJAMUEPROJECT_API UBaseAbility : public UActorComponent, public IAbilityInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBaseAbility();

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FName AbilityName;
protected:

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	AActor* starActor;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UPrimitiveComponent* RootPrimitiveComponent;


	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UInputAction* activateAbilityInputAction;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UInputAction* deactivateAbilityInputAction;
	
	// Called when the game starts
	virtual void BeginPlay() override;

	//IAbilityInterface implementations
	virtual FName GetAbilityName_Implementation() const override;
	
	virtual bool CanActivate_Implementation() const override;

	//Cooldown
	virtual float GetCooldown_Implementation() const override;
	virtual bool IsOnCooldown_Implementation() const override;
	

	UPROPERTY(EditAnywhere)
	float Cooldown;
	UPROPERTY(VisibleAnywhere)
	float CurrentCooldownTimer;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	virtual void ActivateAbility_Implementation(const FInputActionValue& value) override;
	virtual void DeactivateAbility_Implementation() override;
	virtual void BindInput_Implementation(UEnhancedInputComponent* InputComponent) override;
};

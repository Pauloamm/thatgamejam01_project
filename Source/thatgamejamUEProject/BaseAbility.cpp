// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAbility.h"

// Sets default values for this component's properties
UBaseAbility::UBaseAbility()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
}


// Called when the game starts
void UBaseAbility::BeginPlay()
{
	Super::BeginPlay();
	starActor = GetOwner();
	CurrentCooldownTimer = Cooldown;
	RootPrimitiveComponent = Cast<UPrimitiveComponent>(starActor->GetAttachParentActor()->GetRootComponent());
	UE_LOG(LogTemp, Warning, TEXT("ROOT COMPONENET: %s"), *RootPrimitiveComponent->GetName());

	// ...
	
}

FName UBaseAbility::GetAbilityName_Implementation() const
{
	return this->AbilityName;
}

void UBaseAbility::ActivateAbility_Implementation(const FInputActionValue& value)
{
	UE_LOG(LogTemp, Warning, TEXT("Activating Ability"));
}

void UBaseAbility::DeactivateAbility_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Deactivating Ability"));
}

void UBaseAbility::BindInput_Implementation(UEnhancedInputComponent* InputComponent)
{
	//BASE ABILITY IS "ABSTRACT"
}

bool UBaseAbility::CanActivate_Implementation() const
{
	//Simple cooldown restriction
	return !Execute_IsOnCooldown(this);
}

float UBaseAbility::GetCooldown_Implementation() const
{
	return Cooldown;
}

bool UBaseAbility::IsOnCooldown_Implementation() const
{
	return CurrentCooldownTimer < Cooldown; 
}


// Called every frame
void UBaseAbility::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CurrentCooldownTimer += DeltaTime;
	
	// ...
}





// Fill out your copyright notice in the Description page of Project Settings.


#include "GrapplingHookAbility.h"

#include "EnhancedInputComponent.h"
#include "Star.h"

UGrapplingHookAbility::UGrapplingHookAbility():Super()
{
	bIsPushingTowardsStar=false;
}

void UGrapplingHookAbility::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bIsPushingTowardsStar) return;
	
	
	
	FVector PullDirection = starActor->GetActorLocation() - RootPrimitiveComponent->GetComponentLocation();

	if (PullDirection.Size() < deadZoneRadiusAroundStar)
		Execute_DeactivateAbility(this);

	//Draw Debug Direction
	DrawDebugLine(
		GetWorld(),
		starActor->GetActorLocation(),
		RootPrimitiveComponent->GetComponentLocation(),
		FColor::Yellow,
		false,
		5,
		0,
		3.0f
	);
	
	PullDirection.Normalize();
	RootPrimitiveComponent->AddForce(PullDirection*DeltaTime*pullForce,NAME_None,true);

	
}

void UGrapplingHookAbility::ActivateAbility_Implementation(const FInputActionValue& value)
{
	if (!Execute_CanActivate(this)) return;
	Super::ActivateAbility_Implementation(value);
	
	bIsPushingTowardsStar= true; // activates force towards star
	AStar* star = Cast<AStar>(starActor);
	star->LockInPlace(true);

	// Directly set new velocity with same magnitude to still kepp velocity
	float currentSpeed = RootPrimitiveComponent->GetPhysicsLinearVelocity().Size();
	FVector NewDirection = starActor->GetActorLocation() - RootPrimitiveComponent->GetComponentLocation();
	NewDirection.Normalize();
	NewDirection *= currentSpeed; 
	RootPrimitiveComponent->SetPhysicsLinearVelocity(NewDirection);

	DrawDebugSphere(
				GetWorld(), 
				starActor->GetActorLocation(), 
				deadZoneRadiusAroundStar, 
				25, 
				FColor::Blue, 
				false, 
				2, 
				0, 
				1.0f
			);

}

void UGrapplingHookAbility::DeactivateAbility_Implementation()
{
	if (!bIsPushingTowardsStar) return;
	Super::DeactivateAbility_Implementation(); // logs
	Cast<AStar>(starActor)->LockInPlace(false);

	CurrentCooldownTimer = 0; // start cooldown
	bIsPushingTowardsStar = false;

}

void UGrapplingHookAbility::BindInput_Implementation(UEnhancedInputComponent* InputComponent)
{
	InputComponent->BindAction(this->activateAbilityInputAction, ETriggerEvent::Started,this,&UGrapplingHookAbility::ActivateAbility_Implementation);

	InputComponent->BindAction(this->deactivateAbilityInputAction,ETriggerEvent::Completed,this,&UGrapplingHookAbility::DeactivateAbility_Implementation);
	//InputComponent->BindAction(this->deactivateAbilityInputAction,ETriggerEvent::Canceled,this,&UGrapplingHookAbility::DeactivateAbility_Implementation);

}


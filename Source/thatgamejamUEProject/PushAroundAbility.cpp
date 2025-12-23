// Fill out your copyright notice in the Description page of Project Settings.


#include "PushAroundAbility.h"

#include "Pushable.h"


UPushAroundAbility::UPushAroundAbility():Super()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPushAroundAbility::DeactivateAbility_Implementation()
{
	Super::DeactivateAbility_Implementation();
}

void UPushAroundAbility::ActivateAbility_Implementation(const FInputActionValue& value)
{
	if (!Execute_CanActivate(this)) return;
	
	Super::ActivateAbility_Implementation(value); // prints it activated

	this->CurrentCooldownTimer = 0;
	FVector centerPushLocation = starActor->GetActorLocation();
	
	// Setup collision query
	FCollisionShape Sphere = FCollisionShape::MakeSphere(this->PushRadius);
	FCollisionQueryParams QueryParams;
	//QueryParams.AddIgnoredActor(starActor); // Don't detect the star itself
	
	// Array to store overlap results
	TArray<FOverlapResult> OverlapResults;

	bool bFoundOverlaps = GetWorld()->OverlapMultiByChannel(
		OverlapResults, // results
		centerPushLocation, //position
		FQuat::Identity, // rotation
		ECC_Pawn, // Check pawn channel (adjust if needed)
		Sphere, // shape
		QueryParams// query params
	);
	
	//TEMPORARY DEBUG
	DrawDebugSphere(
				GetWorld(), 
				centerPushLocation, 
				PushRadius, 
				25, 
				FColor::Red, 
				false, 
				3, 
				0, 
				1.0f
			);

	
	if (!bFoundOverlaps) return;

	UE_LOG(LogTemp, Warning, TEXT("PushAroundAbility: Found %d overlapping actors"), OverlapResults.Num());
	
	for (const FOverlapResult& overlapResult : OverlapResults)
	{
		AActor* actorHit = overlapResult.GetActor();
		if (actorHit->Implements<UPushable>())
			this->PushActor(actorHit);
			
	}

		
	
			
	
}

void UPushAroundAbility::PushActor(AActor* actorToPush)
{
	FVector pushDirection = actorToPush->GetActorLocation() - starActor->GetActorLocation();
	pushDirection.Normalize();

	//Draw Debug Direction
	DrawDebugLine(
		GetWorld(),
		actorToPush->GetActorLocation(),
		starActor->GetActorLocation(),
		FColor::Yellow,
		false,
		5,
		0,
		3.0f
	);

	// BTS- check for implementation- check for overriding in bps, then calls c++
	// if direct cast here, ignores blueprints implementations
	IPushable::Execute_OnPushed(actorToPush, pushDirection, this->PushForce);  

	
}


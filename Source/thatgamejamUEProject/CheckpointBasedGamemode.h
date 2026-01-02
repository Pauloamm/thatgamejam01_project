// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CheckpointBasedGamemode.generated.h"

/**
 * 
 */
UCLASS()
class THATGAMEJAMUEPROJECT_API ACheckpointBasedGamemode : public AGameModeBase
{
	GENERATED_BODY()


public:
	FTransform* RespawnTransform;
	
	UFUNCTION(BlueprintCallable, Category = "CheckpointBasedGamemode")
	void RespawnPlayerControlledSoul(APlayerController* playerController, AActor* playerActorToDestroy);


};

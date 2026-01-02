// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckpointBasedGamemode.h"

#include "ControlledSoul.h"

void ACheckpointBasedGamemode::RespawnPlayerControlledSoul(APlayerController* playerController, AActor* playerActorToDestroy)
{
	playerActorToDestroy->Destroy();
	UE_LOG(LogTemp, Display, TEXT("PLAYER MORREU"));

	
	APawn* newPlayerPawn = Cast<APawn>(GetWorld()->SpawnActor(AControlledSoul::StaticClass(),this->RespawnTransform));
	playerController->Possess(newPlayerPawn);

	
}

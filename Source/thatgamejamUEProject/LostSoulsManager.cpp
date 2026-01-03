#include "LostSoulsManager.h"
#include "Kismet/GameplayStatics.h"

ALostSoulsManager::ALostSoulsManager()
{
	PrimaryActorTick.bCanEverTick = false;
    
	// Default thresholds - override in editor
	DoorThresholds = { 3, 7, 10,12,15 };
}

void ALostSoulsManager::CollectSoul()
{
	CollectedSouls++;
	CheckThresholds();
}

void ALostSoulsManager::CheckThresholds()
{
	while (OpenedDoors < DoorThresholds.Num() && 
		   CollectedSouls >= DoorThresholds[OpenedDoors])
	{
		OnDoorThresholdReached.Broadcast(OpenedDoors);
		OpenedDoors++;
	}
}

int32 ALostSoulsManager::GetSoulsUntilNextDoor() const
{
	if (OpenedDoors >= DoorThresholds.Num())
		return 0;
	return DoorThresholds[OpenedDoors] - CollectedSouls;
}

ALostSoulsManager* ALostSoulsManager::Get(UWorld* World)
{
	return Cast<ALostSoulsManager>(
		UGameplayStatics::GetActorOfClass(World, ALostSoulsManager::StaticClass())
	);
}
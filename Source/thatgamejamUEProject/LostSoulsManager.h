#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LostSoulsManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDoorThresholdReached, int32, DoorIndex);

UCLASS()
class THATGAMEJAMUEPROJECT_API ALostSoulsManager : public AActor
{
	GENERATED_BODY()

public:
	ALostSoulsManager();

	UPROPERTY(BlueprintAssignable)
	FOnDoorThresholdReached OnDoorThresholdReached;

	// Thresholds: door 0 opens at index 0 value, door 1 at index 1, etc.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Souls")
	TArray<int32> DoorThresholds;

	UPROPERTY(BlueprintReadOnly, Category = "Souls")
	int32 CollectedSouls = 0;

	UFUNCTION(BlueprintCallable, Category = "Souls")
	void CollectSoul();

	UFUNCTION(BlueprintCallable, Category = "Souls")
	int32 GetSoulsUntilNextDoor() const;

	// Easy access from anywhere
	static ALostSoulsManager* Get(UWorld* World);

private:
	int32 OpenedDoors = 0;
	void CheckThresholds();
};
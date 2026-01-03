#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SoulDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDoorOpened);

UCLASS()
class THATGAMEJAMUEPROJECT_API ASoulDoor : public AActor
{
	GENERATED_BODY()

public:
	ASoulDoor();

	UPROPERTY(BlueprintAssignable, Category = "Door")
	FOnDoorOpened OnDoorOpened;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Door")
	int32 DoorIndex = 0;

	UPROPERTY(EditAnywhere, Category = "Door")
	float OpenDuration = 0.5f;

	UPROPERTY(EditAnywhere, Category = "Door")
	float SlideDistance = 200.f;

private:
	bool bIsOpening = false;
	float Progress = 0.f;
	FVector ClosedLocation;

	UFUNCTION()
	void OnThresholdReached(int32 Index);

	void Open();
};
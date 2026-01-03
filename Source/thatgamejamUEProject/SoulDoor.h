#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SoulDoor.generated.h"

UCLASS()
class THATGAMEJAMUEPROJECT_API ASoulDoor : public AActor
{
	GENERATED_BODY()

public:
	ASoulDoor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Door")
	int32 DoorIndex = 0;

	UPROPERTY(EditAnywhere, Category = "Door")
	FVector OpenOffset = FVector(0, 0, 300);

	UPROPERTY(EditAnywhere, Category = "Door")
	float OpenDuration = 1.0f;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DoorMesh;

private:
	FVector ClosedLocation;
	bool bIsOpen = false;

	UFUNCTION()
	void OnThresholdReached(int32 Index);
};
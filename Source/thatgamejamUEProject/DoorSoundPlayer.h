#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DoorSoundPlayer.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class THATGAMEJAMUEPROJECT_API UDoorSoundPlayer : public UActorComponent
{
	GENERATED_BODY()

public:
	UDoorSoundPlayer();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* OpenSound;

private:
	UFUNCTION()
	void PlayOpenSound();
};
#include "DoorSoundPlayer.h"
#include "SoulDoor.h"
#include "Kismet/GameplayStatics.h"

UDoorSoundPlayer::UDoorSoundPlayer()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UDoorSoundPlayer::BeginPlay()
{
	Super::BeginPlay();

	ASoulDoor* Door = Cast<ASoulDoor>(GetOwner());
	if (Door)
	{
		Door->OnDoorOpened.AddDynamic(this, &UDoorSoundPlayer::PlayOpenSound);
	}
}

void UDoorSoundPlayer::PlayOpenSound()
{
	if (OpenSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, OpenSound, GetOwner()->GetActorLocation());
	}
}
#include "SoulDoor.h"
#include "LostSoulsManager.h"
#include "Kismet/GameplayStatics.h"

ASoulDoor::ASoulDoor()
{
	PrimaryActorTick.bCanEverTick = false;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	RootComponent = DoorMesh;
}

void ASoulDoor::BeginPlay()
{
	Super::BeginPlay();
	ClosedLocation = GetActorLocation();

	if (ALostSoulsManager* Manager = ALostSoulsManager::Get(GetWorld()))
	{
		Manager->OnDoorThresholdReached.AddDynamic(this, &ASoulDoor::OnThresholdReached);
	}
}

void ASoulDoor::OnThresholdReached(int32 Index)
{
	if (Index != DoorIndex || bIsOpen)
		return;

	bIsOpen = true;

	// Simple lerp - for jam, you could also just SetActorLocation instantly
	FVector TargetLocation = ClosedLocation + OpenOffset;
    
	// Using a timeline or latent action would be cleaner, 
	// but for a jam this quick approach works:
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	UKismetSystemLibrary::MoveComponentTo(
		DoorMesh, 
		TargetLocation, 
		GetActorRotation(),
		false, false, 
		OpenDuration, 
		false,
		EMoveComponentAction::Move,
		LatentInfo
	);
}
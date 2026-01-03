#include "SoulDoor.h"
#include "LostSoulsManager.h"

ASoulDoor::ASoulDoor()
{
	PrimaryActorTick.bCanEverTick = true;
	bIsOpening = false;
}

void ASoulDoor::BeginPlay()
{
	Super::BeginPlay();

	ClosedLocation = GetActorLocation();

	if (ALostSoulsManager* Manager = ALostSoulsManager::Get(GetWorld()))
	{
		UE_LOG(LogTemp, Warning, TEXT("ENCONTROU MANAGER E ADICIONOU LISTENER"));

		Manager->OnDoorThresholdReached.AddDynamic(this, &ASoulDoor::OnThresholdReached);
	}
}

void ASoulDoor::OnThresholdReached(int32 Index)
{
	UE_LOG(LogTemp, Warning, TEXT("Received Index: %d, My DoorIndex: %d, bIsOpening: %s"), 
	   Index, DoorIndex, bIsOpening ? TEXT("true") : TEXT("false"));

	if (Index == DoorIndex)
	{
		UE_LOG(LogTemp, Warning, TEXT("Index matches!"));
	}
    
	if (!bIsOpening)
	{
		UE_LOG(LogTemp, Warning, TEXT("Not opening yet!"));
	}

	if (Index == DoorIndex && !bIsOpening)
	{
		Open();
	}

	if (Index == DoorIndex && !bIsOpening)
	{
		UE_LOG(LogTemp, Warning, TEXT("HORA DE ABRIR"));

		Open();
	}
}

void ASoulDoor::Open()
{
	OnDoorOpened.Broadcast();
	Progress = 0.f;
	bIsOpening = true;
}

void ASoulDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsOpening) return;

	Progress += DeltaTime / OpenDuration;

	if (Progress >= 1.f)
	{
		SetActorLocation(ClosedLocation + FVector(SlideDistance, 0.f, 0.f));
		bIsOpening = false;
		return;
	}

	float Alpha = FMath::InterpEaseOut(0.f, 1.f, Progress, 2.f);
	SetActorLocation(ClosedLocation + FVector(SlideDistance * Alpha, 0.f, 0.f));
}
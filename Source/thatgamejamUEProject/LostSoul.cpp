#include "LostSoul.h"

#include "ControlledSoul.h"
#include "LostSoulsManager.h"
#include "Kismet/GameplayStatics.h"

ALostSoul::ALostSoul()
{
	PrimaryActorTick.bCanEverTick = true;	

}

void ALostSoul::BeginPlay()
{
	Super::BeginPlay();
	

	CollisionSphere = Cast <UPrimitiveComponent>(GetRootComponent());
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ALostSoul::OnOverlapBegin);


	sprite = Cast <UPaperSpriteComponent>(GetComponentByClass(UPaperSpriteComponent::StaticClass()));
	SpriteRelativeStartLocation = sprite->GetRelativeLocation();
}

void ALostSoul::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
								UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
								bool bFromSweep, const FHitResult& SweepResult)
{
	
	AControlledSoul* playerControlledSoul = Cast<AControlledSoul>(OtherActor);
	if (playerControlledSoul == nullptr) return;// failed cast, not the player
	
	// Notify manager
	if (ALostSoulsManager* Manager = ALostSoulsManager::Get(GetWorld()))
	{
		Manager->CollectSoul();
	}

	// Effects
	if (CollectSound)
		UGameplayStatics::PlaySoundAtLocation(this, CollectSound, GetActorLocation());
    
	if (CollectEffect)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), CollectEffect, GetActorLocation());

	Destroy();
}

void ALostSoul::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RunningTime += DeltaTime;
	
	float Offset = FMath::Sin(RunningTime * FloatSpeed) * FloatAmplitude;
	sprite->SetRelativeLocation(SpriteRelativeStartLocation + FVector(0.f, 0.f, Offset));
}

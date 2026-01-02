// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckpointTrigger.h"

#include "CheckpointBasedGamemode.h"
#include "ControlledSoul.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACheckpointTrigger::ACheckpointTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	


}

// Called when the game starts or when spawned
void ACheckpointTrigger::BeginPlay()
{
	Super::BeginPlay();
	TriggerComponent= this->GetComponentByClass<UPrimitiveComponent>();
	UE_LOG(LogTemp, Display, TEXT("TRIGGERBOX"));

	TriggerComponent->OnComponentBeginOverlap.AddDynamic(this,&ACheckpointTrigger::OnCheckpointOverlap);

}


void ACheckpointTrigger::OnCheckpointOverlap(UPrimitiveComponent* thisComponent,AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{

	AControlledSoul* playerControlledSoul = Cast<AControlledSoul>(OtherActor);
	if (playerControlledSoul == nullptr) return;// failed cast, not the player

	UE_LOG(LogTemp, Display, TEXT("NOVO CHECKPOINT"));

	AGameModeBase* gamemode = UGameplayStatics::GetGameMode(GetWorld());
	ACheckpointBasedGamemode* currentGamemode = Cast<ACheckpointBasedGamemode>(gamemode);
	if (currentGamemode->RespawnTransform == nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("RESPAWN NULO, DANDO VALOR INICIAL"));
		currentGamemode->RespawnTransform = new FTransform();

	}
	currentGamemode->RespawnTransform->SetLocation(this->GetActorLocation()); 

	
}

void ACheckpointTrigger::OnCheckpointEndOverlap(AActor* OtherActor,  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AControlledSoul* playerControlledSoul = Cast<AControlledSoul>(OtherActor);
	if (playerControlledSoul != nullptr) return;// failed cast, not the player

	ACheckpointBasedGamemode* currentGamemode = Cast<ACheckpointBasedGamemode>(UGameplayStatics::GetGameMode(GetWorld()));
	currentGamemode->RespawnPlayerControlledSoul(Cast<APlayerController>(playerControlledSoul->GetController()),playerControlledSoul);
	
}

// Called every frame
void ACheckpointTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


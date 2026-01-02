// Fill out your copyright notice in the Description page of Project Settings.


#include "SpikeHazard.h"

#include "ControlledSoul.h"

// Sets default values
ASpikeHazard::ASpikeHazard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpikeHazard::BeginPlay()
{
	Super::BeginPlay();
	collider = this->GetComponentByClass<UPrimitiveComponent>();
	collider->OnComponentHit.AddDynamic(this,&ASpikeHazard::OnPlayerCollisionWithHazard);


}

void ASpikeHazard::OnPlayerCollisionWithHazard(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AControlledSoul* playerPawn = Cast<AControlledSoul>(OtherActor);

	if (playerPawn == nullptr) return; // not the player that collision, do nothing

	playerPawn->KillPlayer();
	
}

// Called every frame
void ASpikeHazard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperSpriteComponent.h"
#include "LostSoul.generated.h"


UCLASS()
class THATGAMEJAMUEPROJECT_API ALostSoul : public AActor
{
	GENERATED_BODY()

public:
	ALostSoul();

protected:
	virtual void BeginPlay() override;
	

	UPROPERTY(VisibleAnywhere)
	UPrimitiveComponent* CollisionSphere;

	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* CollectSound;

	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* CollectEffect;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
						bool bFromSweep, const FHitResult& SweepResult);


	UPROPERTY(VisibleAnywhere)
	UPaperSpriteComponent* sprite; 

	UPROPERTY(EditAnywhere, Category = "Float")
	float FloatAmplitude = 10.f;

	UPROPERTY(EditAnywhere, Category = "Float")
	float FloatSpeed = 2.f;

private:
	
	float RunningTime = 0.f;
	FVector SpriteRelativeStartLocation;

	virtual void Tick(float DeltaTime) override;
};
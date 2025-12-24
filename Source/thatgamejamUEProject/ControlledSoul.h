// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystemInterface.h"
#include "Pushable.h"
#include "GameFramework/Character.h"
#include "GameFramework/Pawn.h"
#include "ControlledSoul.generated.h"

UCLASS()
class THATGAMEJAMUEPROJECT_API AControlledSoul : public ACharacter, public IPushable
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AControlledSoul();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	UEnhancedInputComponent* enhancedInputComponent;

	// Input 
	UPROPERTY(EditAnywhere,Category="Input")
	UInputMappingContext* controlledSoulMappingContext;

	UPROPERTY(EditAnywhere,Category="Input")
	UInputAction* horizontalMovementAction;

	UPROPERTY(EditAnywhere,Category="Input")
	UInputAction* JumpAction; 
	
	UFUNCTION()
	virtual void SetupMappingContext(APlayerController* currentController);

	UFUNCTION()
	virtual void SetupBindActions(APlayerController* currentController);

	UFUNCTION()
	virtual void MoveHorizontally(const FInputActionValue& value);
	


	//Camera 
	UPROPERTY(VisibleAnywhere, Category="Camera")
	USceneComponent* camera;

	UPROPERTY(EditAnywhere,Category="Camera")
	FVector cameraOffset;


	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
	virtual void OnPushed_Implementation(FVector PushDirection, float Force) override;

	UPROPERTY(EditAnywhere, Category="Speed")
	FVector Velocity;

	UPrimitiveComponent* RootPhysicsComponent;

	UFUNCTION(BlueprintCallable)
	void CustomJumpImpulse(const FInputActionValue& value);

	UPROPERTY(EditAnywhere,Category="Jump")
	float jumpImpulseForce;
	
};

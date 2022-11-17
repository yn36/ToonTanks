// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 *
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent *SpringArm;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent *Camera;

	UPROPERTY(EditAnywhere, Category = "移动")
	float Speed = 200.f;

	UPROPERTY(EditAnywhere, Category = "移动")
	float TurnRate = 45.f;

	void Move(float Value);
	void Turn(float Value);

	APlayerController *PlayerControlleRef;

public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	virtual void Tick(float DeltaTime) override;
};

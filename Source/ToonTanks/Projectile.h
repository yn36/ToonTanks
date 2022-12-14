// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = "战斗")
	class UProjectileMovementComponent *ProjectileMovementComponent;

private:
	UPROPERTY(EditDefaultsOnly, Category = "战斗")
	UStaticMeshComponent *ProjectileMesh;

	UFUNCTION()
	void OnHit(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &HitResult);

	UPROPERTY(EditAnywhere)
	float Damage = 50.f;

	UPROPERTY(EditAnywhere, Category = "战斗")
	class UParticleSystem *HitParticle;

	UPROPERTY(VisibleAnywhere, Category = "战斗")
	class UParticleSystemComponent *TrailParticle;

	UPROPERTY(EditAnywhere, Category = "战斗")
	class USoundBase *LaunchSound;

	UPROPERTY(EditAnywhere, Category = "战斗")
	USoundBase *HitSound;
};

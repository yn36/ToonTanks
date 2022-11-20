// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
  SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
  SpringArm->SetupAttachment(RootComponent);

  Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
  Camera->SetupAttachment(SpringArm);
}

void ATank::BeginPlay()
{
  Super::BeginPlay();

  TankPlayerControlle = Cast<APlayerController>(GetController());
}

void ATank::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

  if (TankPlayerControlle)
  {
    FHitResult HitResult;
    TankPlayerControlle->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
    RotateTurret(HitResult.ImpactPoint);
  }
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
  Super::SetupPlayerInputComponent(PlayerInputComponent);

  PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
  PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);

  PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

void ATank::Move(float Value)
{
  FVector DeltaLocation = FVector::ZeroVector;
  DeltaLocation.X = Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
  AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float Value)
{
  FRotator DeltalRotator = FRotator::ZeroRotator;
  DeltalRotator.Yaw = Value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
  AddActorLocalRotation(DeltalRotator, true);
}

void ATank::HandleDestruction()
{
  Super::HandleDestruction();
  SetActorHiddenInGame(true);
  SetActorTickEnabled(false);
}
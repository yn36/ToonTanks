// Fill out your copyright notice in the Description page of Project Settings.

#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::ActorDied(AActor *DiedActor)
{
  if (DiedActor == Tank)
  {
    Tank->HandleDestruction();
    if (ToonTanksPlayerController)
    {
      ToonTanksPlayerController->SetPlayerEnabledState(false);
    }
  }
  else if (ATower *DestroyedTower = Cast<ATower>(DiedActor))
  {
    DestroyedTower->HandleDestruction();
  }
}

void AToonTanksGameMode::BeginPlay()
{
  Super::BeginPlay();
  HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart()
{
  Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
  ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
  StartGame();
  if (ToonTanksPlayerController)
  {
    ToonTanksPlayerController->SetPlayerEnabledState(false);

    FTimerHandle PlayerEnabledTimerHandle;
    FTimerDelegate PlayerEnabledTimerDelegate = FTimerDelegate::CreateUObject(ToonTanksPlayerController, &AToonTanksPlayerController::SetPlayerEnabledState, true);
    GetWorldTimerManager().SetTimer(PlayerEnabledTimerHandle, PlayerEnabledTimerDelegate, Startdelay, false);
  }
}
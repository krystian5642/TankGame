// Fill out your copyright notice in the Description page of Project Settings.


#include "FightAndWinGameMode.h"
#include "PlayableTank.h"
#include "EnemyTank.h"
#include "Kismet/GameplayStatics.h"
#include "TankGamePlayerController.h"

// Called when the game starts or when spawned
void AFightAndWinGameMode::BeginPlay()
{
	Super::BeginPlay();
    HandleGameStart();
    Player = Cast<APlayableTank>(UGameplayStatics::GetPlayerPawn(this,0));
    PlayerController = Cast<ATankGamePlayerController>(UGameplayStatics::GetPlayerController(this,0));
}

void AFightAndWinGameMode::HandleGameStart()
{
    TArray<AActor*> ArrayOfEnemies;
    UGameplayStatics::GetAllActorsOfClass(this,AEnemyTank::StaticClass(),ArrayOfEnemies);
    EnemiesNumber=ArrayOfEnemies.Num();
}

void AFightAndWinGameMode::ActorDeath(AActor* DeadActor)
{
    if(DeadActor == Player)
    {
        Player->Death();
        if(PlayerController)
        {
            PlayerController->SetPlayerControllerState(false);
        }
    }
    else if(AEnemyTank* Enemy  = Cast<AEnemyTank>(DeadActor))
    {
        Enemy->Death();
    }
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTank.h"
#include "PlayableTank.h"
#include "Kismet/GameplayStatics.h"

AEnemyTank::AEnemyTank()
{

}

void AEnemyTank::BeginPlay()
{
	Super::BeginPlay();
    PlayerTank = Cast<APlayableTank>(UGameplayStatics::GetPlayerPawn(this,0));
}

// Called every frame
void AEnemyTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if(PlayerTank)
    {
        LookForPlayer();
    }
}

void AEnemyTank::LookForPlayer()
{
    FVector PlayerLocation = PlayerTank->GetActorLocation();
    TurretRotationAt(PlayerLocation);
}
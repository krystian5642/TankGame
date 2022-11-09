// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTank.h"
#include "PlayableTank.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

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
    if(GameMode && GameMode->IsGamePlaying())
    {
        if(PlayerTank)
        {
            LookForPlayer();
        }
        if(IsPlayerInRange())
        {
            Fire();
        }
    }
}

void AEnemyTank::LookForPlayer()
{
    FVector PlayerLocation = PlayerTank->GetActorLocation();
    TurretRotationAt(PlayerLocation);
}

bool AEnemyTank::IsPlayerInRange()
{   
    if(PlayerTank)
    {
        FHitResult HitPlayer;
        FVector LineStart = ProjectileSpawnPoint->GetComponentLocation();
        FVector LineEnd = LineStart + ProjectileSpawnPoint->GetComponentRotation().Vector()*TankFireRange;
        bool SomethingFound = GetWorld()->LineTraceSingleByChannel
        (
            HitPlayer,
            LineStart,
            LineEnd,
            ECC_GameTraceChannel1
        );

        if(!SomethingFound) return false;

        //Is not a player hidding behind walls etc.
        bool IsPlayerVisible = false; 
        APlayableTank* Player = Cast<APlayableTank>(HitPlayer.GetActor());
        if(Player && Player == PlayerTank)
        {
            IsPlayerVisible = true;
        }
        bool IsPlayerAlive = PlayerTank->IsTankAlive();

        if(IsPlayerVisible && IsPlayerAlive)
        {
            return true;
        }
    }

    return false;
}

void AEnemyTank::Death()
{
    Super::Death();
    Destroy();
}
    
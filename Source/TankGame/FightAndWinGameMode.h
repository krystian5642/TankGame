// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FightAndWinGameMode.generated.h"

class APlayableTank;

UCLASS()
class TANKGAME_API AFightAndWinGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	void ActorDeath(AActor* DeadActor);

protected:
    // Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);

private:
	UPROPERTY(VisibleAnywhere)
	unsigned int EnemiesNumber = 0;

	void HandleGameStart();

	APlayableTank* Player;

};

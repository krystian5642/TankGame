// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FightAndWinGameMode.generated.h"

class APlayableTank;
class ATankGamePlayerController;

UCLASS()
class TANKGAME_API AFightAndWinGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	void ActorDeath(AActor* DeadActor);

	inline bool IsGamePlaying()const {return DidGameStart;}

protected:
    // Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void ShowStartGameWidget();

	UFUNCTION(BlueprintImplementableEvent)
	void ShowEndGameWidget(bool bWonGame);

	void DoStartGameStuff(); //delay time etc.

	ATankGamePlayerController* PlayerController;

	UPROPERTY(BlueprintReadOnly,Category="Game")
	float StartDelay = 4.f;

	UPROPERTY(VisibleAnywhere,Category="Game")
	bool DidGameStart = false;

	UPROPERTY(VisibleAnywhere,Category="Game")
	bool IsGameOver = false;

private:
	UPROPERTY(VisibleAnywhere)
	unsigned int EnemiesNumber = 0;

	APlayableTank* Player;

	void SetStartGameState();

};

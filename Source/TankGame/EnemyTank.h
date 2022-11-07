// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseTank.h"
#include "EnemyTank.generated.h"

class APlayableTank;

UCLASS()
class TANKGAME_API AEnemyTank : public ABaseTank
{
	GENERATED_BODY()
	
public:
	AEnemyTank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void LookForPlayer();

	APlayableTank* PlayerTank;

	UPROPERTY(EditAnywhere,Category="Combat")
	float TankFireRange =6000; 

	bool IsPlayerInRange();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "PlayableTank.generated.h"

class USpringArmComponent;
class UCameraComponent;
class APlayerController;

UCLASS()
class TANKGAME_API APlayableTank : public ATank
{
	GENERATED_BODY()

public:
	APlayableTank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere,Category = "Object Components")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere,Category = "Object Components")
	UCameraComponent* Camera;

	APlayerController* PlayerController;

	void ControlTurret();
	
};

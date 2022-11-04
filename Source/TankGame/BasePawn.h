// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

class UCapsuleComponent;

UCLASS()
class TANKGAME_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void RotateWheels(float AxisValue);
	void Move(float AxisValue);
	void Turn(float AxisValue);
	void TurretRotationAt(const FVector& LookAtDirection);

	UPROPERTY(EditAnywhere,Category = "Movement")
	float TankSpeed = 1500;    // px/s

	UPROPERTY(EditAnywhere,Category = "Movement")
	float RotationSpeed = 55;  // deg/s

private:
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(VisibleAnywhere,Category="Tank Component")
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere,Category="Tank Component")
	UStaticMeshComponent* BarrelMesh;

	UPROPERTY(VisibleAnywhere,Category="Tank Component")
	TArray<UStaticMeshComponent*> WheelMeshes;

	UPROPERTY(VisibleAnywhere,Category="Tank Component")
	UStaticMeshComponent* TreadMesh;

	UPROPERTY(VisibleAnywhere,Category="Tank Component")
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere,Category="Tank Component");
	USceneComponent* ProjectileSpawnPoint;

	int MovementDirection  =0;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};

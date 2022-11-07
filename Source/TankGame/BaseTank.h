// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BaseTank.generated.h"

class UCapsuleComponent;
class AProjectile;
class UHealthComponent;

UCLASS()
class TANKGAME_API ABaseTank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseTank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void RotateWheels(float AxisValue);
	void TurretRotationAt(const FVector& LookAtDirection);
	void Fire();

	UPROPERTY(EditAnywhere,Category = "Movement")
	float TankSpeed = 1500;

	UPROPERTY(EditAnywhere,Category = "Movement")
	float TurnSpeed = 55;

	UPROPERTY(EditAnywhere)
	float TurretInterpSpeed = 1;

	UPROPERTY(EditAnywhere)
	float ReloadingTime = 2;

	int MovementDirection  =0;
	
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

	UPROPERTY(VisibleAnywhere,Category="Tank Component")
	UHealthComponent* Health;

	UPROPERTY(EditDefaultsOnly,Category = "Combat")
	TSubclassOf<AProjectile> Projectile;

	FTimerHandle ReloadTimer;
	bool IsReloaded = false;
	void Reload();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Death();
	
};

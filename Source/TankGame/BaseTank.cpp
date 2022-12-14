// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTank.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "Projectile.h"
#include "HealthComponent.h"
#include "TimerManager.h"
#include "Sound/SoundBase.h"

// Sets default values
ABaseTank::ABaseTank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	RootComponent = CapsuleComponent;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));

	TreadMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TreadMesh"));
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	BarrelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BarrelMesh"));
	Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));

	for(int i=0;i<3;i++)
	{
		FName Name = FName(*("Wheels" + FString::FromInt(i)));
		UStaticMeshComponent* Wheels = CreateDefaultSubobject<UStaticMeshComponent>(Name);
		Wheels->SetupAttachment(BaseMesh);
		WheelMeshes.Add(Wheels);
	}

	BaseMesh->SetupAttachment(CapsuleComponent);
	TreadMesh->SetupAttachment(BaseMesh);

	TurretMesh->SetupAttachment(BaseMesh);
	BarrelMesh->SetupAttachment(TurretMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(BarrelMesh);

}

// Called when the game starts or when spawned
void ABaseTank::BeginPlay()
{
	Super::BeginPlay();
	GameMode = Cast<AFightAndWinGameMode>(UGameplayStatics::GetGameMode(this));
}

// Called every frame
void ABaseTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(GameMode && GameMode->IsGamePlaying() && !StartReload)
	{
		GetWorldTimerManager().SetTimer(ReloadTimer,this,&ABaseTank::Reload,ReloadingTime,false);
		StartReload = true;
	}
}

void ABaseTank::RotateWheels(float AxisValue)
{
	for(UStaticMeshComponent* Wheel : WheelMeshes)
	{
		FVector WheelSize = Wheel->Bounds.GetBox().GetSize();
		float WheelRadius = WheelSize.Z/2;
		FRotator WheelRotation = FRotator(TankSpeed/WheelRadius,0,0) * -1 * AxisValue * UGameplayStatics::GetWorldDeltaSeconds(this);
		WheelRotation=FMath::RadiansToDegrees(WheelRotation);
		Wheel->AddLocalRotation(WheelRotation);
	}
}

void ABaseTank::TurretRotationAt(const FVector& LookAtDirection)
{
	FVector Direction = LookAtDirection - TurretMesh->GetComponentLocation();
	FRotator RotateToTarget(0,Direction.Rotation().Yaw,0);
	TurretMesh->SetWorldRotation
	(
		FMath::RInterpTo
			(
				TurretMesh->GetComponentRotation(),
				RotateToTarget,
				UGameplayStatics::GetWorldDeltaSeconds(this),
				TurretInterpSpeed
			)
	);
}

void ABaseTank::Fire()
{
	if(Projectile && IsReloaded)
	{
		AProjectile* ProjectileSpawned = GetWorld()->SpawnActor<AProjectile>
		(
			Projectile,
			ProjectileSpawnPoint->GetComponentTransform()
		);
		if(ProjectileSpawned)
		{
			ProjectileSpawned->SetOwner(this);
			IsReloaded = false;
			GetWorldTimerManager().SetTimer(ReloadTimer,this,&ABaseTank::Reload,ReloadingTime,false);
			if(FireSound)
			{
				UGameplayStatics::PlaySoundAtLocation(this,FireSound,ProjectileSpawnPoint->GetComponentLocation());
			}
		}
	}	
}

void ABaseTank::Reload()
{
	IsReloaded = true;
	GetWorldTimerManager().ClearTimer(ReloadTimer);
}

void ABaseTank::Death()
{
	//sounds and effects
	IsAlive = false;
}
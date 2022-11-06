// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "Projectile.h"
#include "TimerManager.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	RootComponent = CapsuleComponent;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));

	TreadMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TreadMesh"));
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	BarrelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BarrelMesh"));

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
void ATank::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(ReloadTimer,this,&ATank::Reload,ReloadingTime,false);
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATank::Move(float AxisValue)
{
	FVector LocalOffset = FVector(TankSpeed,0,0) * AxisValue * UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalOffset(LocalOffset,true);
    RotateWheels(AxisValue);
	MovementDirection = AxisValue;
}

void ATank::RotateWheels(float AxisValue)
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

void ATank::Turn(float AxisValue)
{
	FRotator AddRotation;
	if(MovementDirection)
	{
		AddRotation= FRotator(0,TurnSpeed,0) * AxisValue * MovementDirection* 
		UGameplayStatics::GetWorldDeltaSeconds(this);
	}
	else
	{
		AddRotation= FRotator(0,TurnSpeed,0) * AxisValue * 
		UGameplayStatics::GetWorldDeltaSeconds(this);
	}
	AddActorLocalRotation(AddRotation,true);
}

void ATank::TurretRotationAt(const FVector& LookAtDirection)
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

void ATank::Fire()
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
			GetWorldTimerManager().SetTimer(ReloadTimer,this,&ATank::Reload,ReloadingTime,false);
		}
	}	
}

void ATank::Reload()
{
	IsReloaded = true;
	GetWorldTimerManager().ClearTimer(ReloadTimer);
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
ABasePawn::ABasePawn()
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
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasePawn::RotateWheels(float DeltaTime,float AxisValue)
{
	if(!AxisValue)
	{
		return;
	}
	for(UStaticMeshComponent* Wheel : WheelMeshes)
	{
		FVector WheelSize = Wheel->Bounds.GetBox().GetSize();
		float WheelRadius = WheelSize.Z/2;
		FRotator WheelRotation = FRotator(TankSpeed/WheelRadius,0,0) * -1 * AxisValue * DeltaTime;
		WheelRotation=FMath::RadiansToDegrees(WheelRotation);
		Wheel->AddLocalRotation(WheelRotation);
	}
}

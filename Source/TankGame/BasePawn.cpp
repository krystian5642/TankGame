// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"

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

	FrontWheelMesh= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrontWheel"));
	MiddleWheelMesh= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MiddleWheel"));
	BackWheelMesh= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BackWheel"));

	BaseMesh->SetupAttachment(CapsuleComponent);
	TreadMesh->SetupAttachment(BaseMesh);

	TurretMesh->SetupAttachment(BaseMesh);
	BarrelMesh->SetupAttachment(TurretMesh);

	FrontWheelMesh->SetupAttachment(BaseMesh);
	MiddleWheelMesh->SetupAttachment(BaseMesh);
	BackWheelMesh->SetupAttachment(BaseMesh);

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

// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	RootComponent = ProjectileMesh;

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));;
	MovementComponent->MaxSpeed = 3000;
	MovementComponent->InitialSpeed = 2000.f;


}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	if(ProjectileMesh)
	{
		ProjectileMesh->OnComponentHit.AddDynamic(this,&AProjectile::OnHit);
	}
	if(FireExplosion)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this,FireExplosion,
		GetActorLocation(),GetActorRotation());
	}
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent *HitComp, AActor *OtherActor,
	UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit)
{	
	UE_LOG(LogTemp,Display,TEXT("%s  %s  %s"),*HitComp->GetName(),*OtherActor->GetName(),*OtherComp->GetName());
}


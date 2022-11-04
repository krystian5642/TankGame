// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayableTank.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "DrawDebugHelpers.h"

APlayableTank::APlayableTank()
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    Camera  = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

    SpringArm->SetupAttachment(RootComponent);
    Camera->SetupAttachment(SpringArm);
}

void APlayableTank::BeginPlay()
{
    Super::BeginPlay();

    PlayerController = Cast<APlayerController>(GetController());

}

void APlayableTank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    ControlTurret();


}

void APlayableTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("Forward"),this,&APlayableTank::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"),this,&APlayableTank::Turn);

}

void APlayableTank::ControlTurret()
{
    if(PlayerController)
    {
        FHitResult HitByCursor;
        PlayerController->GetHitResultUnderCursor
        (
            ECollisionChannel::ECC_Visibility,
            false,
            HitByCursor
        );
        DrawDebugSphere(GetWorld(),HitByCursor.ImpactPoint,100,20,FColor::Red,false);
        TurretRotationAt(HitByCursor.ImpactPoint);
    }
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayableTank.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

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


}

void APlayableTank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);



}

void APlayableTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("Forward"),this,&APlayableTank::Move);

}

void APlayableTank::Move(float AxisValue)
{
    FVector LocalOffset =-1 *  FVector(TankSpeed,0,0) * AxisValue * UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalOffset(LocalOffset);
}
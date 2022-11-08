// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGamePlayerController.h"

void ATankGamePlayerController::SetPlayerControllerState(bool bControllerState)
{
    if(bControllerState)
    {
        GetPawn()->EnableInput(this);
    }
    else
    {
        GetPawn()->DisableInput(this);
    }
    bShowMouseCursor = bControllerState;
}
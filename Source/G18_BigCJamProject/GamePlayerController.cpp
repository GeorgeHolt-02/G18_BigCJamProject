// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayerController.h"

AGamePlayerController::AGamePlayerController()
{
	SetShowMouseCursor(true);
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	bEnableMouseOverEvents = true;
	bEnableTouchOverEvents = true;

}

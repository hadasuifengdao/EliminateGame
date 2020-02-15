// Fill out your copyright notice in the Description page of Project Settings.

#include "xiaoxiaole.h"
#include "xiaoxiaoleGameMode.h"
#include "xiaoxiaolePawn.h"
#include "xiaoxiaolePlayerController.h"

AxiaoxiaoleGameMode::AxiaoxiaoleGameMode()
{
	DefaultPawnClass = AxiaoxiaolePawn::StaticClass();
	PlayerControllerClass = AxiaoxiaolePlayerController::StaticClass();

}



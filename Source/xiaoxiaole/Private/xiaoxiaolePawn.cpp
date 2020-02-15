// Fill out your copyright notice in the Description page of Project Settings.

#include "xiaoxiaole.h"
#include "Arr.h"
#include "xiaoxiaolePawn.h"
#include"TraceMacro.h"
#include "Block.h"
#include"Classes/Components/InputComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AxiaoxiaolePawn::AxiaoxiaolePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;


}

// Called when the game starts or when spawned
void AxiaoxiaolePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AxiaoxiaolePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

}

void AxiaoxiaolePawn::CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult)
{
	Super::CalcCamera(DeltaTime, OutResult);
	OutResult.Rotation = FRotator(-90.0f, -90.0f, 0.0f);
	OutResult.Location = FVector(0.0f, 0.0f, 3000.0f);
}

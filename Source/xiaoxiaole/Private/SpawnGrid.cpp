// Fill out your copyright notice in the Description page of Project Settings.

#include "xiaoxiaole.h"
#include "SpawnGrid.h"
#include"BlockGrid.h"


// Sets default values
ASpawnGrid::ASpawnGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void ASpawnGrid::BeginPlay()
{
	Super::BeginPlay();
	ABlockGrid* BlockGrid = GetWorld()->SpawnActor<ABlockGrid>(FVector(0.0f, 0.0f, 0.0f), FRotator(0, 0, 0));
	int32 widthOffset=BlockGrid->width;
	int32 heightOffset= BlockGrid->height;
	float BlockSpacing = 200.0f;
	BlockGrid->SetActorLocation(FVector(0.0f-(widthOffset+1)*0.5f*BlockSpacing, 0.0f-(heightOffset+1)*0.5f*BlockSpacing,0.0f));
	
}

// Called every frame
void ASpawnGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// Fill out your copyright notice in the Description page of Project Settings.

#include "xiaoxiaole.h"
#include "BlockMove.h"
#include "Block.h"


// Sets default values
ABlockMove::ABlockMove()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABlockMove::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABlockMove::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ABlockMove::BlockExchange(ABlock* One, ABlock* Two)
{
	FVector Location1 = One->GetActorLocation();
	FVector Location2 = Two->GetActorLocation();
	One->SetActorLocation(Location1);
	Two->SetActorLocation(Location2);


}


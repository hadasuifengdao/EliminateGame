// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include	"Block.h"
#include "BlockMove.generated.h"

UCLASS()
class XIAOXIAOLE_API ABlockMove : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlockMove();
	
	
	void BlockExchange(ABlock* OneBlock, ABlock* TwoBlock);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include"Block.h"
#include"TimerManager.h"
#include "BlockGrid.generated.h"

/*struct Blocks
{
	int32 Address;
	int32 ColorNumber;
	FVector SpawnLocation;
};*/
UCLASS()
class XIAOXIAOLE_API ABlockGrid : public AActor
{
	GENERATED_BODY()
		UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* DummyRoot;
	
	

	
public:	
	// Sets default values for this actor's properties
	ABlockGrid();
	UPROPERTY(Category = Sound, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UAudioComponent* AC;
	USoundBase*SoundBase;
	USoundBase*SoundBase1;
	UFUNCTION(BlueprintCallable, Category = Tile)
		void GameStart();
	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadWrite)
		int32 Size;
	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadWrite)
		int32 width;
	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadWrite)
		int32 height;
	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadWrite)
		int32 Score;

	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
		int32 j;
		int32 i;
		ABlock* FirstBlock;
		ABlock* SecondBlock;
		FTimerHandle Delay;
		FTimerHandle Delay1;
		FTimerHandle Delay2;
		FTimerHandle Delay3;
		FTimerHandle Delay4;
		float BlockSpacing;
		TArray<ABlock*>RemoveList;
		TArray<int32>DropList;
		TArray<ABlock*>Block;
		TArray<int32>BlockAddress;
		TArray<int32>ColorNo;
		TArray<int32>Color;
		TArray<FVector>ReSpawnLocation;
		void CreateBlock(int32 ColorNumber,FVector Location,int32 SpawbAddress,int32 i,int32 j);
		int32 GetBlockAddress(int32 x,int32 y);
		
		ABlock* GetBlockFromAddress(int32 Address);

		FVector GetSpawnLocation(int32 i,int32 j);

		void GetBlock(ABlock* NewBlock);
		
		ABlock* GetCurrentSelectBlock() const { return CurrentSelectBlock; };
		ABlock* CandestroyBlock(ABlock*A, ABlock*B, ABlock*C);

		void SwapBlock(ABlock*A, ABlock*B);
		void DestroyRemovelist();
		bool CanRemove(ABlock*A, ABlock*B, ABlock*C);
		bool CanMove(ABlock*A,ABlock*B);
		void DropBlock();
		void ReSpawnBlock();
		bool Check();
		bool Init();
		void Falling(int32 RowNo, int32 ColNo);
		void WaitMe();
		
		
		
		

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	ABlock* CurrentSelectBlock;
	UPROPERTY(BlueprintReadOnly, Category = Tile)
	int32 Number;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }


	
	
};

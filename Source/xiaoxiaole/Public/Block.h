// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Block.generated.h"
UENUM()
namespace EBlockState
{
	enum Type
	{
		ETS_Falling,
		ETS_Normal,
		ETS_WillDestroy,
		ETS_Swaping
	};
}

UCLASS()
class XIAOXIAOLE_API ABlock : public AActor
{
	GENERATED_BODY()

	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BlockMesh;
	
public:	
	// Sets default values for this actor's properties
	ABlock();
	bool bIsActive;
	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadWrite)
		TEnumAsByte<EBlockState::Type> BlockState;
	UPROPERTY()
		class UMaterial* BaseMaterial;
	UPROPERTY()
		class UMaterialInstance* BlueMaterial;
	UPROPERTY()
		class UMaterialInstance* OrangeMaterial;
	UPROPERTY()
		class UMaterialInstance* RedMaterial;
	UPROPERTY()
		class UMaterialInstance* GreenMaterial;
	

	UFUNCTION()
		void BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);
	UFUNCTION()
		void BlockClicked2(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);
	void Highlight(bool bOn);
	void SetAddress(int32 NewAddress);
	int32 GetAddress();
	void ColorSet(int32 NewNumber);
	int32 ColorGet();
	void SetXY(int32 X,int32 Y);
	int32 GetX();
	int32 GetY();

	UPROPERTY()
		class ABlockGrid* Grid;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadOnly, Category = Tile)
		int32 Address;
	UPROPERTY(BlueprintReadOnly, Category = Tile)
		int32 Number;
	UPROPERTY(BlueprintReadOnly, Category = Tile)
		int32 x;
	UPROPERTY(BlueprintReadOnly, Category = Tile)
		int32 y;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
	FORCEINLINE class UStaticMeshComponent* GetBlockMesh() const { return BlockMesh; }


	
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#include "xiaoxiaole.h"
#include "Block.h"
#include "BlockGrid.h"
#include "TraceMacro.h"


// Sets default values
ABlock::ABlock()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	struct FConstructorStatics
	{
		//StaticMesh'/Game/xiaoxiaole/Meshes/PuzzleCube.PuzzleCube'
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> BaseMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> BlueMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> OrangeMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance>RedMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance>GreenMaterial;
		FConstructorStatics() :PlaneMesh(TEXT("/Game/Puzzle/Meshes/PuzzleCube.PuzzleCube")), BaseMaterial(TEXT("/Game/Puzzle/Meshes/BaseMaterial.BaseMaterial")), BlueMaterial(TEXT("/Game/Puzzle/Meshes/BlueMaterial.BlueMaterial")), OrangeMaterial(TEXT("/Game/Puzzle/Meshes/OrangeMaterial.OrangeMaterial")), RedMaterial(TEXT("/Game/Puzzle/Meshes/RedMaterial.RedMaterial")),GreenMaterial(TEXT("/Game/Puzzle/Meshes/GreenMaterial.GreenMaterial"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;
	
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
	BlockMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());
	BlockMesh->SetRelativeScale3D(FVector(0.8f, 0.8f, 0.25f));
	BlockMesh->SetRelativeLocation(FVector(0.f, 0.f, 25.f));
	BlockMesh->SetMaterial(0, ConstructorStatics.BlueMaterial.Get());
	BlockMesh->SetupAttachment(DummyRoot);
	BlockMesh->OnClicked.AddDynamic(this, &ABlock::BlockClicked);
	BlockMesh->OnClicked.AddDynamic(this, &ABlock::BlockClicked2);
	
	

	BaseMaterial = ConstructorStatics.BaseMaterial.Get();
	BlueMaterial = ConstructorStatics.BlueMaterial.Get();
	OrangeMaterial = ConstructorStatics.OrangeMaterial.Get();
	RedMaterial = ConstructorStatics.RedMaterial.Get();
	GreenMaterial = ConstructorStatics.GreenMaterial.Get();
}


void ABlock::BeginPlay()
{
	Super::BeginPlay();
}
void ABlock::BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	
	if (this->BlockState == EBlockState::ETS_Normal)
	{
		Grid->GetBlock(this);
	}
	
	
}
void ABlock::BlockClicked2(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	
	ABlock* CurrentSelectBlock = Grid->GetCurrentSelectBlock();
	if (CurrentSelectBlock&&CurrentSelectBlock != this)
	{
		BlockClicked(ClickedComp, ButtonClicked);
		
	}

}

void ABlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABlock::Highlight(bool bOn)
{
	if (bIsActive)
	{
		return;
	}
	if (bOn)
	{
		BlockMesh->SetMaterial(0, BaseMaterial);

	}
	else
	{
		BlockMesh->SetMaterial(0, BlueMaterial);
	}
}
void ABlock::ColorSet(int32 NewNumber)
{
	
	Number = NewNumber;
	switch (NewNumber)
	{
	case 1: BlockMesh->SetMaterial(0, BaseMaterial);break;
	case 2: BlockMesh->SetMaterial(0, BlueMaterial);break;
	case 3:	BlockMesh->SetMaterial(0, OrangeMaterial);break;
	case 4:	BlockMesh->SetMaterial(0, RedMaterial);break;
	case 5:BlockMesh->SetMaterial(0, GreenMaterial);break;
	}
	
}
int32 ABlock::ColorGet()
{
	return Number;
}

void ABlock::SetAddress(int32 NewAddress)
{
	Address = NewAddress;
}
int32 ABlock::GetAddress()
{
	return Address;
}
void ABlock::SetXY(int32 X,int32 Y)
{
	x = X;
	y = Y;
}
int32 ABlock::GetX()
{
	return x;
}
int32 ABlock::GetY()
{
	return y;
}


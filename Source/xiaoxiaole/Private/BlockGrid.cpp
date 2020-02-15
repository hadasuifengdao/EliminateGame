// Fill out your copyright notice in the Description page of Project Settings.
#include "xiaoxiaole.h"
#include "BlockGrid.h"
#include "Block.h"
#include "Arr.h"
#include"Components/AudioComponent.h"
#include "TraceMacro.h"
#include"ConstructorHelpers.h"
#include"TimerManager.h"
// Sets default values
ABlockGrid::ABlockGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ConstructorHelpers::FObjectFinderOptional<USoundBase>Sound(TEXT("/Game/exchange.exchange"));
	ConstructorHelpers::FObjectFinderOptional<USoundBase>Sound1(TEXT("/Game/clear.clear"));
	SoundBase = Sound.Get();
	SoundBase1 = Sound1.Get();
	AC = CreateDefaultSubobject<UAudioComponent>(TEXT("AC"));
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;
	BlockSpacing = 240.f;
	width = 7;
	height = 8;

	
}

// Called when the game starts or when spawned
void ABlockGrid::BeginPlay()
{
	
	Super::BeginPlay();
	


}

void ABlockGrid::GameStart()
{
	RemoveList.Empty();
	DropList.Empty();
	Color.Empty(width*height);
	Color.AddUninitialized(Color.Max());
	ReSpawnLocation.Empty(width*height);
	Block.Empty(width*height);
	Block.AddUninitialized(Block.Max());
	int32 Address;
	FVector BlockLocation;
	do
	{

		Init();
	} while (!Init());
	for (i = 0;i < width;i++)
	{
		for (j = 0;j < height;j++)
		{
			Address = GetBlockAddress(i, j);
			BlockLocation = GetSpawnLocation(i, j);
			CreateBlock(Color[i*height + j], BlockLocation, Address, i, j);
		}
	}

}
	// Called every frame
	void ABlockGrid::Tick(float DeltaTime)
	{
		Super::Tick(DeltaTime);

	}
	bool ABlockGrid::Init()
	{
		for (int32 i = 0;i < width;i++)
		{
			for (int32 j = 0;j < height;j++)
			{
				Number = FMath::RandRange(1, 5);
				Color.Add(Number);
			}
		}
		for (int32 m = 0;m < width;m++)
		{
			for (int32 n = 0;n < height;n++)
			{
				if (n < height - 2)
				{
					if (Color[m*height + n] == Color[m*height + n + 1]&& Color[m*height + n + 1] == Color[m*height + n + 2])
					{
						ColorNo.Add(1);
						ColorNo.Add(2);
						ColorNo.Add(3);
						ColorNo.Add(4);
						ColorNo.Add(5);
						ColorNo.Remove(Color[m*height + n]);
						Color[m*height + n + 2] = ColorNo[FMath::RandRange(0, 3)];
						ColorNo.Empty();
					}
				}
			}
		}
		for (int32 x = 0;x < width;x++)
		{
			for (int32 y = 0;y < height;y++)
			{
				if (x < width - 2)
				{
					if (Color[x*height + y] == Color[x*height + y + height] && Color[x*height + y + height] == Color[x*height + y + 2 * height])
					{
						Color.Empty();
						return false;
					}
					
				}
				
			}
		}
		//Color.Empty();
		return true;

	}
	void ABlockGrid::CreateBlock(int32 ColorNumber, FVector Location,int32 SpawnAddress,int32 i,int32 j)//生成Block
	{	
		ABlock* NewBlock = GetWorld()->SpawnActor<ABlock>(Location, FRotator(0, 0, 0));
		NewBlock->ColorSet(ColorNumber);
		NewBlock->Grid = this;
		NewBlock->SetXY(i,j);
		NewBlock->SetAddress(SpawnAddress);
		Block[SpawnAddress] = NewBlock;
		NewBlock->BlockState = EBlockState::ETS_Normal;

	}

	int32 ABlockGrid::GetBlockAddress(int32 x, int32 y)//获取block的位置信息
	{
		if (x < width&&y < height)
		{
			int32 ReturnAddress;
			ReturnAddress = (x * height) + y;
			return ReturnAddress;
		}
		
		return NULL;

	}

	ABlock* ABlockGrid::GetBlockFromAddress(int32 Address)
	{
		return Block[Address];
	}

	FVector ABlockGrid::GetSpawnLocation(int32 i,int32 j)
	{
		
		FVector Location = GetActorLocation() + FVector(i*BlockSpacing,j*BlockSpacing,0);
		return Location;
	}
	void ABlockGrid::GetBlock(ABlock* NewBlock)//获得当前点击的block
	{
		NewBlock->GetBlockMesh()->SetRenderCustomDepth(true);
		if(CurrentSelectBlock)
		{
			CurrentSelectBlock->GetBlockMesh()->SetRenderCustomDepth(false);
			
			if (CurrentSelectBlock != NewBlock)
			{
				NewBlock->GetBlockMesh()->SetRenderCustomDepth(false);
				if (((FMath::Abs(CurrentSelectBlock->GetAddress()-NewBlock->GetAddress())==1&& (FMath::Min(CurrentSelectBlock->GetAddress(), NewBlock->GetAddress()) + 1) % height != 0)|| FMath::Abs(CurrentSelectBlock->GetAddress() - NewBlock->GetAddress()) == height))
				{
					SwapBlock(CurrentSelectBlock, NewBlock);
					UGameplayStatics::PlaySound2D(GetWorld(),SoundBase);
					FirstBlock = CurrentSelectBlock;
					SecondBlock = NewBlock;
					if (Check())
					{
					}
					else
					{
						CurrentSelectBlock->BlockState = ::EBlockState::ETS_Swaping;
						NewBlock->BlockState = ::EBlockState::ETS_Swaping;
						GetWorldTimerManager().SetTimer(Delay3, this, &ABlockGrid::WaitMe,0.2f,false);
						//WaitMe();
						//SwapBlock(CurrentSelectBlock, NewBlock);

					}
					/*if (FMath::Abs(CurrentSelectBlock->GetAddress() - NewBlock->GetAddress()) == 1)
					{
						if ((FMath::Min(CurrentSelectBlock->GetAddress(), NewBlock->GetAddress()) + 1) % height != 0)
						{
							SwapBlock(CurrentSelectBlock, NewBlock);
							FirstBlock = CurrentSelectBlock;
							SecondBlock = NewBlock;
							if (Check())
							{
							}
							else
							{
								WaitMe();
								SwapBlock(CurrentSelectBlock, NewBlock);
								
							}
						}

					}
					if(FMath::Abs(CurrentSelectBlock->GetAddress() - NewBlock->GetAddress()) == height)
					{
						FirstBlock = CurrentSelectBlock;
						SecondBlock = NewBlock;
						SwapBlock(CurrentSelectBlock, NewBlock);
						if (Check())
						{
						}
						else
						{
							SwapBlock(CurrentSelectBlock, NewBlock);

						}
					}*/
					
				}
				
			}
			CurrentSelectBlock = nullptr;
		}
		else
		{
			CurrentSelectBlock = NewBlock;
		}
		
	}
	void ABlockGrid::SwapBlock(ABlock*A, ABlock*B)//交换block的位置
	{
		int32 Address = A->GetAddress();
		int32 Address1 = B->GetAddress();
		FVector location = A->GetActorLocation();
		FVector location1 = B->GetActorLocation();
		int32 x = A->GetX();
		int32 y = A->GetY();
		int32 x1 = B->GetX();
		int32 y1 = B->GetY();
		A->SetActorLocation(location1);
		B->SetActorLocation(location);
		A->SetAddress(Address1);
		B->SetAddress(Address);
		A->SetXY(x1,y1);
		B->SetXY(x,y);
		Block[A->GetAddress()] = A;
		Block[B->GetAddress()] = B;
	}
	bool ABlockGrid::CanRemove(ABlock*A, ABlock*B, ABlock*C)//判断是否可以交换（如果可以消除的话就可以交换）
	{
		if (A->ColorGet() == B->ColorGet() && B->ColorGet() == C->ColorGet())
		{
			return true;
		}
		return false;
	}
	void ABlockGrid::DestroyRemovelist()
	{
		for (int32 x = 0;x<width;x++)
		{
			for (int32 y = 0;y<height;y++)
			{
				if (Block[x*height + y] && Block[x*height + y] != NULL)
				{
					Block[x*height + y]->BlockState = EBlockState::ETS_WillDestroy;
				}
			}

		}
		Score += RemoveList.Num();
		for (int32 i = RemoveList.Num()-1; i >= 0; i--)
		{
			Block[RemoveList[i]->GetAddress()] = NULL;
			RemoveList[i]->Destroy();
			UGameplayStatics::PlaySound2D(GetWorld(),SoundBase1);
		}
		RemoveList.Empty();
		GetWorldTimerManager().SetTimer(Delay1, this, &ABlockGrid::DropBlock, 0.2f, false);
		
	}
	void ABlockGrid::DropBlock()
	{
		for (int32 x = 0;x<width;x++)
		{
			for (int32 y = 0;y<height;y++)
			{
				if (Block[x*height + y] && Block[x*height + y] != NULL)
				{
					Block[x*height + y]->BlockState = EBlockState::ETS_Falling;
				}
			}

		}
		for (int32 i = 0;i < width;i++)
		{
			for (int32 j=0;j<height;j++)
			{
				if (Block[i*height + j] == NULL)
				{
					DropList.Add(j);	
				}
			}
			if (DropList.Num()>0)
			{
				Falling(DropList.Last(),i);
			}
			DropList.Empty();
		}
		if (!Check())
		{
			GetWorldTimerManager().SetTimer(Delay2, this, &ABlockGrid::ReSpawnBlock, 0.2f, false);
		}
		
	}
	void ABlockGrid::Falling(int32 RowNo, int32 ColNo)
	{
		for (int32 i = width - 1;i >= 0;i--)
		{
			for (int32 j = height - 1;j >= 0;j--)
			{
				if (i == ColNo)
				{
					if (j<RowNo)
					{
						if (Block[i*height + j] != NULL)
						{
							Block[i*height + j]->SetActorLocation(Block[i*height + j]->GetActorLocation() + FVector(0.0f, (RowNo - j)*BlockSpacing, 0.0f));
							Block[i*height + j]->SetAddress(Block[i*height + j]->GetAddress() + RowNo - j);
							Block[i*height + RowNo] = Block[i*height + j];
							Block[i*height + j] = NULL;
							RowNo--;
						}
					}
				}

			}
		}


	}

	void ABlockGrid::ReSpawnBlock()
	{
		for (int32 i = width-1;i >=0;i--)
		{
			for (int32 j= height-1;j >=0;j--)
			{
				if (Block[i*height + j] == NULL)
				{
					CreateBlock(FMath::RandRange(1, 3), GetSpawnLocation(i, j), i*height + j, i, j);
				}
			}
		}
		
		if (!Check())
		{
			for (int32 m = 0;m<width;m++)
			{
				for (int32 n = 0;n<height;n++)
				{
					if (Block[m*height + n] && Block[m*height + n] != NULL)
					{
						Block[m*height + n]->BlockState = EBlockState::ETS_Normal;
					}
				}

			}
		}
		
		
	}

	bool ABlockGrid::Check()
	{
		for (int32 i = 0;i<width;i++)
		{
			for (int32 j = 0;j<height;j++)
			{
				if (j<height-2)
				{
					if (Block[i*height + j]&&Block[i*height + j + 1]&&Block[i*height + j + 2])
					{
						if (CanRemove(Block[i*height + j], Block[i*height + j + 1], Block[i*height + j + 2]))
						{
							if (!RemoveList.Contains(Block[i*height + j]))
							{
								RemoveList.Add(Block[i*height + j]);
							}
							if (!RemoveList.Contains(Block[i*height + j + 1]))
							{
								RemoveList.Add(Block[i*height + j + 1]);
							}
							if (!RemoveList.Contains(Block[i*height + j + 2]))
							{
								RemoveList.Add(Block[i*height + j + 2]);
							}
						}

					}
				}
			}
		}
		for (int32 m = 0;m < width;m++)
		{
			for (int32 n = 0;n < height;n++)
			{
				if (m<width- 2)
				{
					if (Block[m*height + n]&&Block[m*height + n + height]&&Block[m*height + n + 2 * height])
					{
						if (CanRemove(Block[m*height + n], Block[m*height + n + height], Block[m*height + n + 2 * height]))
						{
							if (!RemoveList.Contains(Block[m*height + n]))
							{
								RemoveList.Add(Block[m*height + n]);
							}
							if (!RemoveList.Contains(Block[m*height + n + height]))
							{
								RemoveList.Add(Block[m*height + n + height]);
							}
							if (!RemoveList.Contains(Block[m*height + n + 2 * height]))
							{
								RemoveList.Add(Block[m*height + n + 2 * height]);
							}
						}
					}
				}
			}
		}
		
		if (RemoveList.Num() > 0)
		{
			GetWorldTimerManager().SetTimer(Delay, this, &ABlockGrid::DestroyRemovelist, 0.2f, false);
			return true;
		}
			
		
		RemoveList.Empty();
		
		return false;
	}
	void ABlockGrid::WaitMe()
	{
		FirstBlock->BlockState = ::EBlockState::ETS_Normal;
		SecondBlock->BlockState = ::EBlockState::ETS_Normal;
		SwapBlock(FirstBlock, SecondBlock);

	}
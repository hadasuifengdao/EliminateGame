#pragma once
#include"Engine.h"
class ABlock;
struct FGuidList
{
	//GENERATED_BODY()
	TArray<ABlock*> GridBoxList;

	ABlock*& operator [](int32 Index)
	{
		check(Index < GridBoxList.Num());
		return GridBoxList[Index];
	}

	void SetNum(int32 Num)
	{
		GridBoxList.SetNum(Num);
	}
};


class  Array
{
public:
	static Array* getInstance(int32 a, int32 b);
	void addBlock(int32 i, int32 j, ABlock* A);
	ABlock* getBlock(int32 i, int32 j);
	int32 getlength();
	int32 gethigh();
	//void findActive();
private:
	Array(int32 a, int32 b);
	TArray<FGuidList> ListBox;
	static Array* instance;
	int32 length, high;
};


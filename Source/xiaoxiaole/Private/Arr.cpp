#include "xiaoxiaole.h"
#include "Arr.h"
#include "Block.h"
#include "Engine.h"

Array::Array(int32 a, int32 b) {
	length = a;
	high = b;
	ListBox.SetNum(a);
	for (int32 i = 0;i < a;i++)
	{
		ListBox[i].SetNum(b);
	}
}



Array* Array::getInstance(int32 a, int32 b) {
	static Array* instance = new Array(a, b);
	return instance;
}


void Array::addBlock(int32 i, int32 j, ABlock* A)
{
	ListBox[i][j] = A;
}

ABlock* Array::getBlock(int32 i, int32 j)
{
	return ListBox[i][j];
}
int32 Array::getlength()
{
	return length;
}
int32 Array::gethigh()
{
	return high;
}
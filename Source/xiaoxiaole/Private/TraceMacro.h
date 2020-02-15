#pragma once
#include"Engine.h"

//Current Class Name + Function Name where this is called!
#define TRACE_CUR_CLASS_FUNC (FString(__FUNCTION__))

//Current Class where this is called!
#define TRACE_CUR_CLASS (FString(__FUNCTION__).Left(FString(__FUNCTION__).Find(TEXT(":"))) )

//Current Function Name where this is called!
#define TRACE_CUR_FUNC (FString(__FUNCTION__).Right(FString(__FUNCTION__).Len() - FString(__FUNCTION__).Find(TEXT("::")) - 2 ))

//Current Line Number in the code where this is called!
#define TRACE_CUR_LINE  (FString::FromInt(__LINE__))

//Current Class and Line Number where this is called!
#define TRACE_CUR_CLASS_LINE (TRACE_CUR_CLASS + "(" + TRACE_CUR_LINE + ")")

#define TRACE_CUR_CLASS__Fuction_LINE (TRACE_CUR_CLASS_FUNC+ "()"+TRACE_CUR_LINE)

//Current Function Signature where this is called!
#define TRACE_CUR_FUNCSIG (FString(__FUNCSIG__))


//Victory Screen Message
// 	Gives you the Class name and exact line number where you print a message to yourself!
//#define TRACEONSC(Param1) (GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *(TRACE_CUR_CLASS_LINE + ": " + Param1)) )

//#define VSCREENMSG2(Param1,Param2) (GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *(TRACE_CUR_CLASS_LINE + ": " + Param1 + " " + Param2)) )

//#define VSCREENMSGF(Param1,Param2) (GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *(TRACE_CUR_CLASS_LINE + ": " + Param1 + " " + FString::SanitizeFloat(Param2))) )

//UE LOG!
//#define V_LOG(Param1) 		UE_LOG(LogTemp,Warning,TEXT("%s: %s"), *TRACE_CUR_CLASS_LINE, *FString(Param1))

//#define V_LOG2(LogCat, Param1,Param2) 	UE_LOG(LogCat,Warning,TEXT("%s: %s %s"), *TRACE_CUR_CLASS_LINE, *FString(Param1),*FString(Param2))

//#define V_LOGF(LogCat, Param1,Param2) 	UE_LOG(LogCat,Warning,TEXT("%s: %s %f"), *TRACE_CUR_CLASS_LINE, *FString(Param1),Param2)

#define TRACE(FormatString , ...) UE_LOG(LogTemp,Warning,TEXT("%s: %s"), 	*TRACE_CUR_CLASS__Fuction_LINE, *FString::Printf(TEXT(FormatString), ##__VA_ARGS__ ) )
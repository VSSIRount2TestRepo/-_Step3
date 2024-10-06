// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBlueprintFunctionLibrary.h"

void UMyBlueprintFunctionLibrary::MyStringToBytes(const FString string, TArray<uint8> &data)
{
    uint32 size = string.Len();
    data.AddUninitialized(size);
    uint8* dataPtr = data.GetData();
    StringToBytes(string, dataPtr, size);
    for (uint32 i = 0; i < size; i++) {
        *(dataPtr + i) = *(dataPtr + i) + 1;
    }
}
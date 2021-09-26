// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TestSnakeGi.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FRecordData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(BlueprintReadOnly)
        int Apples;
    UPROPERTY(BlueprintReadOnly)
        float Time;
};


UCLASS()
class SNAKETEST_API UTestSnakeGi : public UGameInstance
{
    GENERATED_BODY()
    
protected:

    UPROPERTY(BlueprintReadWrite, EditAnyWhere)
    TMap<FString, FRecordData> RecordMap;

public:

    UFUNCTION(BlueprintCallable)
        void AddRecord(FString playerName, int apple, float time);

};

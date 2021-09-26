// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/TestSnakeGi.h"

void UTestSnakeGi::AddRecord(FString playerName, int apple, float time)
{
    FRecordData localplayerData;

    localplayerData.Apples = apple;
    localplayerData.Time = time;

    RecordMap.Add(playerName, localplayerData);
}

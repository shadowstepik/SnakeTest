// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePiece.generated.h"

UENUM(BlueprintType)
enum class E_PieceType : uint8
{
    None            UMETA(DisplayName = "None"),
    Snake           UMETA(DisplayName = "Snake"),
    Apple           UMETA(DisplayName = "Apple"),
    Wall            UMETA(DisplayName = "Wall"),
};

UCLASS()
class SNAKETEST_API ABasePiece : public AActor
{
    GENERATED_BODY()
    
public:	
    // Sets default values for this actor's properties
    ABasePiece();

    UPROPERTY(BlueprintReadWrite, EditAnyWhere)
        E_PieceType MyType;
    
protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

};

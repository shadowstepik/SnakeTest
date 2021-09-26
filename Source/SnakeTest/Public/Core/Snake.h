// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePiece.h"

#include "Snake.generated.h"

UENUM(BlueprintType)
enum class E_Direction : uint8
{
    Up          UMETA(DisplayName = "Up"),
    Right       UMETA(DisplayName = "Right"),
    Down        UMETA(DisplayName = "Down"),
    Left        UMETA(DisplayName = "Left"),
};

UCLASS()
class SNAKETEST_API ASnake : public APawn
{
    GENERATED_BODY()

public:
    // Sets default values for this pawn's properties
    ASnake();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    
    UPROPERTY(BlueprintReadWrite, EditAnyWhere)
        E_Direction CurrentTargetDirection;

    UPROPERTY(BlueprintReadWrite, EditAnyWhere)
        bool CanInput;

    UPROPERTY(BlueprintReadWrite, EditAnyWhere)
        TArray<ABasePiece*> SnakePieces;

    UPROPERTY(BlueprintReadWrite, EditAnyWhere)
        TSubclassOf<ABasePiece> SnakePieceClass;


    UPROPERTY(BlueprintReadWrite, EditAnyWhere)
        FTransform TargetSpawnTransform;

    UPROPERTY(BlueprintReadWrite, EditAnyWhere)
        TMap<E_Direction, FVector> StepMap;

    UPROPERTY(BlueprintReadWrite, EditAnyWhere)
        bool EatApple;

    UPROPERTY(BlueprintReadWrite, EditAnyWhere)
        bool StopGame;

    UPROPERTY(BlueprintReadWrite, EditAnyWhere)
        int HalfFieldX;

    UPROPERTY(BlueprintReadWrite, EditAnyWhere)
        int HalfFieldY;

    UPROPERTY(BlueprintReadWrite, EditAnyWhere)
        TSubclassOf<ABasePiece> AppleClass;

    UPROPERTY(BlueprintReadWrite, EditAnyWhere)
        int StepSize;

    UPROPERTY(BlueprintReadWrite, EditAnyWhere)
        int EatenApples;

    UPROPERTY(BlueprintReadWrite, EditAnyWhere)
        float GameTimer;

    UPROPERTY(BlueprintReadWrite, EditAnyWhere)
        float SpeedMul;

    bool dataSent;

public:

    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void DirectionToRight();
    void DirectionToLeft();

    // functions
    UFUNCTION(BlueprintCallable)
        void SpawnSnakePiece(E_Direction defaultDirection);

    UFUNCTION(BlueprintCallable)
        void DestroySnakePiece();

    UFUNCTION(BlueprintCallable)
        void StartSnakeSpawn(int startLength);

    UFUNCTION(BlueprintCallable)
        void CheckPiece(E_PieceType& myType, AActor*& hitActor);

    UFUNCTION(BlueprintCallable)
        void SpawnApple();

    // Blueprint implementation
    UFUNCTION(BlueprintImplementableEvent)
        void UpdateScore(int apple, float timer);

    UFUNCTION(BlueprintImplementableEvent)
        void GameOver();

};

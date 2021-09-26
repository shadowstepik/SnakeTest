// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Snake.h"
#include "Kismet/KismetMathLibrary.h"
#include "Core/TestSnakeGi.h"

// Sets default values
ASnake::ASnake()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASnake::BeginPlay()
{
    StartSnakeSpawn(5);
    SpawnApple();

    // Blueprint logica
    Super::BeginPlay();
}

// Called every frame
void ASnake::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (StopGame)
    {
        if (!dataSent)
        {
            Cast<UTestSnakeGi>(GetWorld()->GetGameInstance())->AddRecord("Player" + FString::FromInt(UKismetMathLibrary::RandomIntegerInRange(1,200)), EatenApples, GameTimer);
            GameOver();
            dataSent = true;
        }
    }

    // main loop
    else
    {
        AActor* hitActor;
        E_PieceType myType;
        CheckPiece(myType, hitActor);
        if (myType == E_PieceType::Snake || myType == E_PieceType::Wall)    StopGame = true;

        if (myType == E_PieceType::Apple)
        {
            EatApple = true;
            hitActor->Destroy();
            EatenApples++;
            SpawnApple();
            SetActorTickInterval(GetActorTickInterval() * SpeedMul);
        }

        SpawnSnakePiece(CurrentTargetDirection);
        CanInput = true;

        if (EatApple)
        {
            EatApple = false;
        }
        else
        {
            DestroySnakePiece();
        }
        GameTimer = GameTimer + GetActorTickInterval();

        UpdateScore(EatenApples, GameTimer);
    }
}

// Called to bind functionality to input
void ASnake::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAction("ToRight", IE_Pressed, this, &ASnake::DirectionToRight);
    PlayerInputComponent->BindAction("ToLeft", IE_Pressed, this, &ASnake::DirectionToLeft);
}

void ASnake::DirectionToRight()
{
    if (!CanInput) return;

    CanInput = false;
    
    switch (CurrentTargetDirection)
    {
    case E_Direction::Up:
        CurrentTargetDirection = E_Direction::Right;
        break;
    case E_Direction::Right:
        CurrentTargetDirection = E_Direction::Down;
        break;
    case E_Direction::Down:
        CurrentTargetDirection = E_Direction::Left;
        break;
    case E_Direction::Left:
        CurrentTargetDirection = E_Direction::Up;
        break;

    default:
        break;
    }
}

void ASnake::DirectionToLeft()
{
    if (!CanInput) return;

    CanInput = false;

    switch (CurrentTargetDirection)
    {
    case E_Direction::Up:
        CurrentTargetDirection = E_Direction::Left;
        break;
    case E_Direction::Right:
        CurrentTargetDirection = E_Direction::Up;
        break;
    case E_Direction::Down:
        CurrentTargetDirection = E_Direction::Right;
        break;
    case E_Direction::Left:
        CurrentTargetDirection = E_Direction::Down;
        break;

    default:
        break;
    }
}

void ASnake::SpawnSnakePiece(E_Direction currentDirection)
{
    if (SnakePieces.Num() > 0)
    {
        FVector localVector = *StepMap.Find(currentDirection);
        TargetSpawnTransform.SetLocation(localVector + SnakePieces[0]->GetActorLocation());
    }
    else
    {
        TargetSpawnTransform.SetLocation(GetActorLocation());
    }

    ABasePiece* currentPiece = GetWorld()->SpawnActor<ABasePiece>(SnakePieceClass.Get(), TargetSpawnTransform);

    SnakePieces.Insert(currentPiece, 0);
}

void ASnake::DestroySnakePiece()
{
    SnakePieces[SnakePieces.Num() - 1]->Destroy();
    SnakePieces.RemoveAt(SnakePieces.Num() - 1);
}

void ASnake::StartSnakeSpawn(int startLength)
{
    for (int i = 0; i < startLength; i++)
    {
        SpawnSnakePiece(E_Direction::Right);

    }
}

void ASnake::CheckPiece(E_PieceType& myType, AActor*& hitActor)
{
    FHitResult hitResult;
    FCollisionQueryParams params;
    params.AddIgnoredActor(SnakePieces[0]);

    GetWorld()->LineTraceSingleByObjectType(hitResult, SnakePieces[0]->GetActorLocation(), SnakePieces[0]->GetActorLocation() + *StepMap.Find(CurrentTargetDirection), ECC_WorldDynamic, params);
    
    if (hitResult.bBlockingHit)
    {
        hitActor = hitResult.GetActor();
        ABasePiece* localPiece = Cast<ABasePiece>(hitResult.GetActor());
        myType = localPiece->MyType;
    }
    else
    {
        hitActor = nullptr;
        myType = E_PieceType::None;
    }
}

void ASnake::SpawnApple()
{
    for (int i = 0; i < 1000; i++)
    {
        FVector testSpawnLocation;

        testSpawnLocation.X = UKismetMathLibrary::RandomIntegerInRange(HalfFieldX / StepSize * -1, HalfFieldX / StepSize) * StepSize;
        testSpawnLocation.Y = UKismetMathLibrary::RandomIntegerInRange(HalfFieldY / StepSize * -1, HalfFieldY / StepSize) * StepSize;
        testSpawnLocation.Z = 0;

        FVector startLocation = testSpawnLocation;
        startLocation.Z = startLocation.Z + 1000;

        FVector endLocation = testSpawnLocation;
        endLocation.Z = endLocation.Z - 100;

        FHitResult hitResult;
        FCollisionQueryParams params;

        GetWorld()->LineTraceSingleByObjectType(hitResult, startLocation, endLocation, ECC_WorldDynamic, params);

        if (hitResult.bBlockingHit && Cast<ABasePiece>(hitResult.GetActor())) continue;

        FTransform spawnTransform;
        spawnTransform.SetLocation(testSpawnLocation);

        GetWorld()->SpawnActor<ABasePiece>(AppleClass.Get(), spawnTransform);

        return;
    }
}


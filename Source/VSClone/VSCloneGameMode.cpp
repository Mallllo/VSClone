// Copyright Epic Games, Inc. All Rights Reserved.

#include "VSCloneGameMode.h"
#include "VSClonePlayerController.h"
#include "VSCloneCharacter.h"
#include "EnemyCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet\GameplayStatics.h"

AVSCloneGameMode::AVSCloneGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	// use our custom PlayerController class
	PlayerControllerClass = AVSClonePlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}

void AVSCloneGameMode::BeginPlay()
{
	Super::BeginPlay();
	UWorld *World = GetWorld();

	if (ensure(World))
	{
		if (ensure(EnemyClass))
		{
			FActorSpawnParameters Parameters = FActorSpawnParameters();
			AEnemyCharacter *SpawnedEnemy;
			for (int i = 0; i < MaxEnemyPoolCount; i++)
			{
				SpawnedEnemy = World->SpawnActor<AEnemyCharacter>(EnemyClass, FVector(500 * i, 0, -1000), FRotator::ZeroRotator, Parameters);
				if (ensure(SpawnedEnemy))
				{
					SpawnedEnemy->SetEnabled(false);
					EnemyPool.Add(SpawnedEnemy);
				}
			}
		}
	}
}

void AVSCloneGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	EnemySpawnCounter -= DeltaTime;
	UE_LOG(LogTemp, Warning, TEXT("EnemySpawnCounter: %f"), EnemySpawnCounter);
	if(EnemySpawnCounter<=0.0f)
	{
		UE_LOG(LogTemp,Warning,TEXT("EnemySpawnCounter<=0.0f"));
		Spawn();
		EnemySpawnCounter = EnemySpawnDuration;
	}
}

void AVSCloneGameMode::Spawn()
{
	for (AEnemyCharacter *Enemy : EnemyPool)
	{
		if (!Enemy->GetEnabled())
		{
			Enemy->SetEnabled(true);
			FVector PlayerLocation = UGameplayStatics::GetPlayerCharacter(this, 0)->GetActorLocation();
			FVector Forward = FVector(FMath::RandRange(EnemySpawnMinRadius, EnemySpawnMaxRadius), 0, 0);
			FQuat RandomRotation = FQuat(FVector(0, 0, 1), FMath::RandRange(0.0, UE_DOUBLE_TWO_PI));
			FVector SpawnPosition = RandomRotation.RotateVector(PlayerLocation + Forward);

			Enemy->SetActorLocation(SpawnPosition);
			GEngine->AddOnScreenDebugMessage(0, 0.5, FColor::Green,TEXT("EnemySpawned"));
			return;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(0, 0.5, FColor::Green,TEXT("Enemy Spawn Failed"));
		}
	}
}
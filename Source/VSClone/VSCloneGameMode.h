// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "VSCloneGameMode.generated.h"

UCLASS(minimalapi)
class AVSCloneGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AVSCloneGameMode();
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditDefaultsOnly, Category = EnemySpawner)
	int MaxEnemyPoolCount = 100;
	UPROPERTY(EditDefaultsOnly, Category = EnemySpawner)
	float EnemySpawnMinRadius = 1500;
	UPROPERTY(EditDefaultsOnly, Category = EnemySpawner)
	float EnemySpawnMaxRadius = 2000;
	UPROPERTY(EditDefaultsOnly, Category = EnemySpawner)
	float EnemySpawnDuration = 0.5f;
protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AEnemyCharacter> EnemyClass;
	float EnemySpawnCounter = 0.0f;
	TArray<class AEnemyCharacter*> EnemyPool;
	void Spawn();
};




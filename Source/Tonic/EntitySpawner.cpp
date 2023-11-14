// Fill out your copyright notice in the Description page of Project Settings.


#include "EntitySpawner.h"

// Sets default values
AEntitySpawner::AEntitySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AEntitySpawner::BeginPlay()
{
	Super::BeginPlay();

	EntitySpawns.Sort([](const FEntitySpawnParameters& Entity1, const FEntitySpawnParameters& Entity2)
	{
		return Entity1.Beat > Entity2.Beat;
	});
}

// Called every frame
void AEntitySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEntitySpawner::SpawnEntities(int32 CurrentBeat)
{
	int32 NumSpawns = EntitySpawns.Num();
	while (NumSpawns > 0 && EntitySpawns[NumSpawns - 1].Beat <= CurrentBeat + SpawnBeatOffset)
	{
		const FEntitySpawnParameters& SpawnParameters = EntitySpawns.Pop();
		NumSpawns--;

		SpawnEntity(SpawnParameters);
	}
}

void AEntitySpawner::SpawnEntity(FEntitySpawnParameters SpawnParameters)
{
	UE_LOG(
		LogTemp,
		Display,
		TEXT("Spawning entity of type %d toward direction %d with length %d."),
		SpawnParameters.EntityType,
		SpawnParameters.EntityDirection,
		SpawnParameters.Length);
}


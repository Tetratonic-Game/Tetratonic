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

	EntitySpawns.Sort();
}

// Called every frame
void AEntitySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEntitySpawner::SpawnEntities(int32 CurrentBeat)
{}

// Fill out your copyright notice in the Description page of Project Settings.


#include "StartBeat.h"

// Sets default values
AStartBeat::AStartBeat()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

// Called when the game starts or when spawned
void AStartBeat::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AStartBeat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


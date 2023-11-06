// Fill out your copyright notice in the Description page of Project Settings.


#include "Adversary.h"

// Sets default values
AAdversary::AAdversary()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAdversary::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAdversary::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	SetActorLocation(GetActorLocation() + (Velocity * DeltaTime));
}


// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Adversary.generated.h"

UCLASS()
class TONIC_API AAdversary : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AAdversary();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	FVector Velocity = FVector(100, 0, 0);

};

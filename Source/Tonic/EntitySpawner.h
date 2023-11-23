// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ExtendableEntity.h"
#include "GameFramework/Actor.h"
#include "EntitySpawner.generated.h"

UENUM(BlueprintType)
enum class EEntityType : uint8
{
	TestEntity UMETA(DisplayName="Test Entity"),
	AdversaryEntity UMETA(DisplayName="Adversary"),
	RewardEntity UMETA(DisplayName="Reward"),
};

USTRUCT(BlueprintType)
struct FEntitySpawnParameters
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Beat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEntityType EntityType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEntityDirection EntityDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Length = 0;

	bool operator<(const FEntitySpawnParameters& Other) const
	{
		return Beat < Other.Beat;
	}
};

UCLASS()
class TONIC_API AEntitySpawner : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AEntitySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SpawnEntities(int32 CurrentBeat);

private:
	UPROPERTY(EditAnywhere)
	TArray<FEntitySpawnParameters> EntitySpawns;

	UPROPERTY(EditAnywhere)
	float EntityVelocity = 200;

	UPROPERTY(EditAnywhere)
	int32 SpawnBeatOffset = 4;

	UPROPERTY(EditAnywhere)
	int32 DespawnBeatOffset;

	UPROPERTY(EditAnywhere)
	AActor* TestEntityActor;

	UPROPERTY(EditAnywhere)
	AActor* AdversaryActor;

	UPROPERTY(EditAnywhere)
	AActor* RewardActor;

	void SpawnEntity(FEntitySpawnParameters SpawnParameters);
	
};

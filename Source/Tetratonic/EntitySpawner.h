// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ExtendableEntity.h"
#include "GameFramework/Actor.h"
#include "EntitySpawner.generated.h"

UENUM(BlueprintType)
enum class EEntityType : uint8
{
	PickupEntity UMETA(DisplayName="Pickup"),
	AdversaryEntity UMETA(DisplayName="Adversary"),
};

USTRUCT(BlueprintType)
struct FEntitySpawnParameters
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEntityType EntityType = EEntityType::PickupEntity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEntityDirection EntityDirection = EEntityDirection::Right;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEntityTarget TargetPosition = EEntityTarget::Center;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TargetBeat = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float NumBeats = 0;

	bool operator<(const FEntitySpawnParameters& Other) const
	{
		return TargetBeat < Other.TargetBeat;
	}
};

UCLASS(DefaultToInstanced)
class TETRATONIC_API AEntitySpawner : public AActor
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

	UFUNCTION(BlueprintCallable)
	TArray<FEntitySpawnParameters> GetEntitiesToSpawn(int32 CurrentBeat);

	UFUNCTION(BlueprintCallable)
	void SortEntities();

	UFUNCTION(BlueprintImplementableEvent)
	void SpawnEntity(TSubclassOf<AExtendableEntity> EntityClass, EEntityDirection EntityDirection, EEntityTarget TargetPosition, int32 TargetBeat, float NumBeats, float Speed);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AExtendableEntity> AdversaryClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AExtendableEntity> PickupClass;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	int32 StartBeat = 1;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	float EntitySpeed = 100;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	TArray<FEntitySpawnParameters> EntitySpawns;

private:
	UPROPERTY(EditAnywhere)
	int32 SpawnBeatOffset = 4;
	
};

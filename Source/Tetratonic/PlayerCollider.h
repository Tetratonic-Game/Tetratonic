// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PlayerCollider.generated.h"

UENUM(BlueprintType)
enum class EAccuracyType : uint8
{
	Okay UMETA(DisplayName="okay"),
	Good UMETA(DisplayName="good"),
	Great UMETA(DisplayName="great"),
	Perfect UMETA(DisplayName="perfect"),
};

UCLASS( DefaultToInstanced, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TETRATONIC_API UPlayerCollider : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPlayerCollider();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly)
	TMap<EAccuracyType, int32> AccuracyScoreModifiers;

	UPROPERTY(EditDefaultsOnly)
	TMap<EAccuracyType, int32> AccuracyHealthModifiers;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIncreasesCombo;

private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};

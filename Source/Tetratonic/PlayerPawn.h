// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ExtendableEntity.h"
#include "PlayerCollider.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class TETRATONIC_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void DisplacePawn(const FVector NormalizedDirection);

	UFUNCTION(BlueprintCallable)
	void ReturnToOrigin();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void HandleCollider(EAccuracyType Accuracy, bool bIncreasesCombo);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetCurrentBeatOffset() const;

	UFUNCTION()
	void EvaluateTimingEvent(const TMap<EAccuracyType, int32>& AccuracyScoreModifiers, const TMap<EAccuracyType, int32>& AccuracyHealthModifiers, bool bIncreasesCombo);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int32 GetScore() const;

	UFUNCTION(BlueprintCallable)
	void AddToScore(const int32 ScoreModifier);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int32 GetCombo() const;

	UFUNCTION(BlueprintCallable)
	void IncreaseCombo();

	UFUNCTION(BlueprintCallable)
	void ResetCombo();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int32 GetHealth() const;

	UFUNCTION(BlueprintCallable)
	void AddToHealth(const int32 HealthModifier);

	UFUNCTION(BlueprintCallable)
	bool SetCurrentPosition(const EEntityTarget NewPosition);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	EEntityTarget GetCurrentPosition() const;

	UPROPERTY(BlueprintReadWrite)
	float InputDisplacement;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 StartingHealth = 100;

	UPROPERTY(BlueprintReadOnly)
	UQuartzClockHandle* ClockHandle;

private:
	UStaticMeshComponent* GetPlayerMesh() const;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere)
	FVector OriginPosition = FVector(0, 0, 0);
	
	UPROPERTY(EditDefaultsOnly)
	int32 StartingScore = 0;

	UPROPERTY(EditDefaultsOnly)
	int32 StartingCombo = 0;

	UPROPERTY(EditDefaultsOnly)
	int32 MaxCombo = 8;
	
	EEntityTarget CurrentPosition = EEntityTarget::Center;
	
	int32 Score;

	int32 Combo;

	int32 Health;
};

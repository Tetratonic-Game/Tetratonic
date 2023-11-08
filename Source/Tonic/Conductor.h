// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Quartz/QuartzSubsystem.h"
#include "Conductor.generated.h"

/**
 * 
 */
UCLASS()
class TONIC_API AConductor : public AActor
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnBeat(FName ClockName, EQuartzCommandQuantization QuantizationType, int32 NumBars, int32 Beat, float BeatFraction);

	UFUNCTION(BlueprintImplementableEvent)
	void OnQuartzReady();

	UPROPERTY(BlueprintReadWrite)
	UQuartzClockHandle* QuartzClock;

private:
	UPROPERTY(EditAnywhere)
	float BeatsPerMinute = 120;
	
	UPROPERTY(EditAnywhere)
	int32 NumBeats = 4;

	UPROPERTY(EditAnywhere)
	EQuartzTimeSignatureQuantization BeatType = EQuartzTimeSignatureQuantization::QuarterNote;
};

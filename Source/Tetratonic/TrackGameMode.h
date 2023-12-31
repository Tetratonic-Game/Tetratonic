// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/AudioComponent.h"
#include "GameFramework/GameModeBase.h"
#include "TrackGameMode.generated.h"


/**
 * 
 */
UCLASS()
class TETRATONIC_API ATrackGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
    // Called when the game starts or when spawned
	virtual void StartPlay() override;
	
    virtual void BeginPlay() override;

public:
	void PlayAudioTrack();

	UPROPERTY(BlueprintReadWrite)
	UQuartzClockHandle* QuartzClock;

	UPROPERTY(BlueprintReadWrite)
	FOnQuartzMetronomeEventBP MetronomeEvent;

	UPROPERTY(BlueprintReadWrite)
	UAudioComponent* AudioComponent;

	UFUNCTION(BlueprintCallable)
	void SetPaused(bool bPaused);
	
	UFUNCTION(BlueprintCallable)
	void GetCorrectedTimestamp(int32& Bars, int32& Beat, float& BeatFraction, float& Seconds) const;

private:
	UPROPERTY(EditAnywhere)
	USoundBase* AudioTrack;
	
	UPROPERTY(EditAnywhere)
	float BeatsPerMinute = 120;
	
	UPROPERTY()
	int32 NumBeats = 4;

	UPROPERTY()
	EQuartzTimeSignatureQuantization BeatType = EQuartzTimeSignatureQuantization::QuarterNote;

	UPROPERTY(EditAnywhere)
	float StartDelay = 0;

	UPROPERTY(EditAnywhere)
	float FadeInDuration = 0;

	UPROPERTY(EditAnywhere)
	float FadeVolumeLevel = 1;

	UPROPERTY(EditAnywhere)
	EAudioFaderCurve FaderCurve = EAudioFaderCurve::Linear;

	UFUNCTION()
	void OnAudioComponentQuantized(EQuartzCommandDelegateSubType CommandType, FName Name);

	FTimerHandle TimerHandle_StartDelay;

	int32 StartBeat = 1;

	float StartTime = 0;
};

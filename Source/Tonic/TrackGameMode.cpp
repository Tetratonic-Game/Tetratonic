// Fill out your copyright notice in the Description page of Project Settings.


#include "TrackGameMode.h"

#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Quartz/AudioMixerClockHandle.h"

void ATrackGameMode::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Display, TEXT("Game mode initializing Quartz clock"));
	const UWorld* World = GetWorld();
	UQuartzSubsystem* QuartzSubsystem = UQuartzSubsystem::Get(World);

	FQuartzClockSettings ClockSettings = FQuartzClockSettings();
	ClockSettings.TimeSignature.NumBeats = NumBeats;
	ClockSettings.TimeSignature.BeatType = BeatType;

	FQuartzQuantizationBoundary QuantizationBoundary = FQuartzQuantizationBoundary();
	QuantizationBoundary.Quantization = EQuartzCommandQuantization::Beat;
	QuantizationBoundary.CountingReferencePoint = EQuarztQuantizationReference::BarRelative;

	// MetronomeEvent = FOnQuartzMetronomeEventBP();
	// MetronomeEvent.BindUFunction(this, "OnBeat");
	
	QuartzClock = QuartzSubsystem->CreateNewClock(this, FName("ConductorClock"), ClockSettings);
	QuartzClock->SetBeatsPerMinute(World, QuantizationBoundary, FOnQuartzCommandEventBP(), QuartzClock, BeatsPerMinute);
	// QuartzClock->SubscribeToQuantizationEvent(World, EQuartzCommandQuantization::Beat, MetronomeEvent, QuartzClock);

	if (StartDelay > 0)
	{
		World->GetTimerManager().SetTimer(TimerHandle_StartDelay, this, &ATrackGameMode::PlayAudioTrack, StartDelay);
	}
	else
	{
		PlayAudioTrack();
	}
}

void ATrackGameMode::PlayAudioTrack()
{
	if (!AudioTrack)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayAudioTrack invoked on game mode, but no audio track was set."));
		return;
	}
	if (!QuartzClock)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayAudioTrack invoked on game mode, but Quartz Clock is not initialized."));
		return;
	}

	UE_LOG(LogTemp, Display, TEXT("Got command to play audio track: %s"), *AudioTrack->GetName());
	
	const UWorld* World = GetWorld();

	UAudioComponent* AudioComponent = UGameplayStatics::CreateSound2D(World, AudioTrack);

	FQuartzQuantizationBoundary TrackBoundary = FQuartzQuantizationBoundary();
	TrackBoundary.Quantization = EQuartzCommandQuantization::Bar;
	TrackBoundary.CountingReferencePoint = EQuarztQuantizationReference::CurrentTimeRelative;

	FOnQuartzCommandEventBP CommandEvent = FOnQuartzCommandEventBP();
	CommandEvent.BindUFunction(this, "OnAudioComponentQuantized");
	AudioComponent->PlayQuantized(World, QuartzClock, TrackBoundary, CommandEvent, StartTime, FadeInDuration, FadeVolumeLevel, FaderCurve);

	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_StartDelay);
}

void ATrackGameMode::OnAudioComponentQuantized(EQuartzCommandDelegateSubType CommandType, FName)
{
	if (CommandType == EQuartzCommandDelegateSubType::CommandOnQueued)
	{
		QuartzClock->StartClock(GetWorld(), QuartzClock);
	}
}





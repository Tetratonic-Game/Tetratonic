// Fill out your copyright notice in the Description page of Project Settings.


#include "Conductor.h"

#include "Quartz/AudioMixerClockHandle.h"


void AConductor::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Display, TEXT("The conductor is working!"));
	const UWorld* World = GetWorld();
	UQuartzSubsystem* QuartzSubsystem = UQuartzSubsystem::Get(World);

	FQuartzClockSettings ClockSettings = FQuartzClockSettings();
	ClockSettings.TimeSignature.NumBeats = NumBeats;
	ClockSettings.TimeSignature.BeatType = BeatType;

	FQuartzQuantizationBoundary QuantizationBoundary = FQuartzQuantizationBoundary();
	QuantizationBoundary.Quantization = EQuartzCommandQuantization::Beat;
	QuantizationBoundary.CountingReferencePoint = EQuarztQuantizationReference::BarRelative;

	FOnQuartzMetronomeEventBP MetronomeEvent = FOnQuartzMetronomeEventBP();
	MetronomeEvent.BindUFunction(this, "OnBeat");

	QuartzClock = QuartzSubsystem->CreateNewClock(this, FName("ConductorClock"), ClockSettings);
	QuartzClock->SetBeatsPerMinute(World, QuantizationBoundary, FOnQuartzCommandEventBP(), QuartzClock, BeatsPerMinute);
	QuartzClock->SubscribeToQuantizationEvent(World, EQuartzCommandQuantization::Beat, MetronomeEvent, QuartzClock);

	OnQuartzReady();

	QuartzClock->StartClock(World, QuartzClock);
}

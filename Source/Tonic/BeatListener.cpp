// Fill out your copyright notice in the Description page of Project Settings.


#include "BeatListener.h"

#include "BeatListenerInterface.h"
#include "TrackGameMode.h"
#include "Quartz/AudioMixerClockHandle.h"

// Sets default values for this component's properties
UBeatListener::UBeatListener()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UBeatListener::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	if (!Owner->Implements<UBeatListenerInterface>())
	{
		UE_LOG(LogTemp, Error, TEXT("BeatListener component was attached to %s, but this actor does not implement IBeatListenerInterface."), *Owner->GetActorNameOrLabel());
		return;
	}

	const UWorld* World = GetWorld();
	ATrackGameMode* TrackGameMode = Cast<ATrackGameMode>(World->GetAuthGameMode());
	if (!TrackGameMode)
	{
		UE_LOG(LogTemp, Error, TEXT("BeatListener for %s could not attach to Quartz subsystem as the current game mode is not a TrackGameMode."), *Owner->GetActorNameOrLabel());
		return;
	}
	if (!TrackGameMode->QuartzClock)
	{
		UE_LOG(LogTemp, Error, TEXT("BeatListener for %s could not be attached as target game mode does not have an active Quartz clock."), *Owner->GetActorNameOrLabel());
		return;
	}
	
	FOnQuartzMetronomeEventBP MetronomeEvent = FOnQuartzMetronomeEventBP();
	MetronomeEvent.BindUFunction(Owner, "OnBeat");
	TrackGameMode->QuartzClock->SubscribeToQuantizationEvent(World, EQuartzCommandQuantization::Beat, MetronomeEvent, TrackGameMode->QuartzClock);
}

// Called every frame
void UBeatListener::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPawn.h"
#include "CoreMinimal.h"
#include "EnhancedInputSubsystems.h"
#include "TrackGameMode.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	Score = StartingScore;
	Health = StartingHealth;
	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);	
		}
	}

	const UWorld* World = GetWorld();
	const ATrackGameMode* TrackGameMode = Cast<ATrackGameMode>(World->GetAuthGameMode());
	if (!TrackGameMode)
	{
		UE_LOG(LogTemp, Error, TEXT("BeatListener for %s could not attach to Quartz subsystem as the current game mode is not a TrackGameMode."), *Owner->GetActorNameOrLabel());
		return;
	}

	InputDisplacement = TrackGameMode->GetPlayfieldRadius();
	ClockHandle = TrackGameMode->QuartzClock;
}

void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float APlayerPawn::GetCurrentBeatOffset() const
{
	if (!ClockHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("ClockHandle was not valid when calling GetCurrentBeatOffset on Player Pawn."))
		return -1;
	}

	const FQuartzTransportTimeStamp Timestamp = ClockHandle->GetCurrentTimestamp(GetWorld());
	const float BeatFraction = ClockHandle->GetBeatProgressPercent();

	const float TimestampError = FMath::Abs(Timestamp.BeatFraction - BeatFraction);
	const float SelectedFraction = (TimestampError > 0.1 || TimestampError < 0.9) ? Timestamp.BeatFraction : BeatFraction;
	
	return (SelectedFraction > 0.5) ? 1 - SelectedFraction : SelectedFraction;
}

void APlayerPawn::EvaluateTimingEvent(const TMap<EAccuracyType, int32>& AccuracyScoreModifiers, const TMap<EAccuracyType, int32>& AccuracyHealthModifiers, bool bIncreasesCombo)
{
	const float BeatOffset = GetCurrentBeatOffset();

	EAccuracyType Accuracy;
	if (BeatOffset < 0.075)
	{
		Accuracy = EAccuracyType::Perfect;
	}
	else if (BeatOffset < 0.15)
	{
		Accuracy = EAccuracyType::Great;
	}
	else if (BeatOffset < 0.3)
	{
		Accuracy = EAccuracyType::Good;
	}
	else
	{
		Accuracy = EAccuracyType::Okay;
	}
	
	AddToScore(AccuracyScoreModifiers[Accuracy]);
	AddToHealth(AccuracyHealthModifiers[Accuracy]);
	if (bIncreasesCombo)
	{
		IncreaseCombo();
	}

	HandleCollider(Accuracy, bIncreasesCombo);
}


void APlayerPawn::DisplacePawn(const FVector NormalizedDirection)
{
	UStaticMeshComponent* PlayerMesh = GetPlayerMesh();
	PlayerMesh->SetRelativeLocation((NormalizedDirection * InputDisplacement) + OriginPosition);
}

void APlayerPawn::ReturnToOrigin()
{
	SetCurrentPosition(EEntityTarget::Center);
	
	UStaticMeshComponent* PlayerMesh = GetPlayerMesh();
	PlayerMesh->SetRelativeLocation(OriginPosition);
}

UStaticMeshComponent* APlayerPawn::GetPlayerMesh() const
{
	UStaticMeshComponent* PlayerMesh = FindComponentByClass<UStaticMeshComponent>();
	
	return PlayerMesh;
}

int32 APlayerPawn::GetScore() const
{
	return Score;
}

void APlayerPawn::AddToScore(const int32 ScoreModifier)
{
	Score += ScoreModifier * (Combo + 1);
}

int32 APlayerPawn::GetCombo() const
{
	return Combo;
}

void APlayerPawn::IncreaseCombo()
{
	if (Combo < MaxCombo)
	{
		++Combo;
	}
}

void APlayerPawn::ResetCombo()
{
	Combo = 0;
}

int32 APlayerPawn::GetHealth() const
{
	return Health;
}

void APlayerPawn::AddToHealth(const int32 HealthModifier)
{
	Health += HealthModifier;
}

bool APlayerPawn::SetCurrentPosition(const EEntityTarget NewPosition)
{
	if (CurrentPosition != NewPosition)
	{
		CurrentPosition = NewPosition;
		return true;
	}
	return false;
}

EEntityTarget APlayerPawn::GetCurrentPosition() const
{
	return CurrentPosition;
}



// Fill out your copyright notice in the Description page of Project Settings.


#include "ExtendableEntity.h"

#include "PlayerCollider.h"
#include "TrackGameMode.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AExtendableEntity::AExtendableEntity()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	
	StartCapComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StartCap"));
	SetRootComponent(StartCapComponent);
	
	EndCapComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EndCap"));
}

// Called when the game starts or when spawned
void AExtendableEntity::BeginPlay()
{
	Super::BeginPlay();

	const FRotator TargetPositionRotator = FRotator(90 * static_cast<int>(TargetPosition), 0, 0);
	TargetPositionOffset = static_cast<bool>(TargetPosition) * TargetPositionRotator.Vector() * 100;

	TrackGameMode = Cast<ATrackGameMode>(GetWorld()->GetAuthGameMode());
	if (TrackGameMode)
	{
		ClockHandle = TrackGameMode->QuartzClock;
	}
}

void AExtendableEntity::OnConstruction(const FTransform& Transform)
{
	if (SpannerCollisionComponent)
	{
		SpannerCollisionComponent->DestroyComponent();
	}
	
	if (!StartCapComponent || !EndCapComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("ExtendableEntity %s does not have start or end cap components, skipping construction."), *GetActorNameOrLabel());
	}
	EndCapComponent->AttachToComponent(StartCapComponent, FAttachmentTransformRules::KeepRelativeTransform);

	if (static_cast<int>(Direction) % 2 == 1)
	{
		Speed = Speed * FMath::Sqrt(2.0f);
	}
	
	StartCapComponent->SetStaticMesh(StartCapMesh);
	EndCapComponent->SetStaticMesh(EndCapMesh);

	StartCapComponent->SetMaterial(0, StartCapMaterial);
	EndCapComponent->SetMaterial(0, EndCapMaterial);

	EndCapComponent->SetRelativeLocation(FVector(-1, 0, 0) * Speed * NumBeats);
	
	if (NumBeats >= 0.5)
	{
		SpannerCollisionComponent = NewObject<UBoxComponent>(this);
		SpannerCollisionComponent->AttachToComponent(StartCapComponent, FAttachmentTransformRules::KeepRelativeTransform);
		SpannerCollisionComponent->SetBoxExtent(FVector((Speed * (NumBeats - 0.5)) / 2, 1, 5));
		SpannerCollisionComponent->SetRelativeLocation(FVector(-1, 0, 0) * ((Speed * NumBeats) / 2));
		SpannerCollisionComponent->RegisterComponent();
	}

	const FRotator MovementRotator = FRotator(45 * static_cast<int>(Direction), 0, 0);
	StartCapComponent->SetRelativeRotation(MovementRotator);
}


// Called every frame
void AExtendableEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ClockHandle)
	{
		int32 TimestampBar;
		int32 TimestampBeat;
		float TimestampBeatFraction;
		float TimestampSeconds;

		TrackGameMode->GetCorrectedTimestamp(TimestampBar, TimestampBeat, TimestampBeatFraction, TimestampSeconds);

		const float BeatFraction = ClockHandle->GetBeatProgressPercent();
		
		float BeatOffset = (TimestampBar - 1) * 4 + (TimestampBeat - TargetBeat);
		if (!UseDiscreteMotion)
		{
			const float TimestampError = FMath::Abs(TimestampBeatFraction - BeatFraction);
			float SelectedFraction = BeatFraction;
			
			if (TimestampError > 0.9)		// Adjust for wrap-around of beat fraction on downbeat
			{
				BeatOffset += 1;
			}
			else if (TimestampError > 0.1)	// Adjust for potential desync when unpausing
			{
				SelectedFraction = TimestampBeatFraction;
			}
			
			const float FractionComponent = 1 - FMath::Sqrt(1 - FMath::Pow(SelectedFraction, 2));
			BeatOffset += FractionComponent;
		}
		
		SetActorLocation(GetActorForwardVector() * Speed * BeatOffset + TargetPositionOffset);
	}
}

void AExtendableEntity::SetLocationBasedOnBeat(const int32 CurrentBeat)
{
	const float BeatOffset = CurrentBeat - TargetBeat;
	const FRotator TargetPositionRotator = FRotator(90 * static_cast<int>(TargetPosition), 0, 0);
	TargetPositionOffset = static_cast<bool>(TargetPosition) * TargetPositionRotator.Vector() * 100;
	SetActorLocation(GetActorForwardVector() * Speed * BeatOffset + TargetPositionOffset);
}



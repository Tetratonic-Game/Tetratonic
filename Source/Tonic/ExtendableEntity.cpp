// Fill out your copyright notice in the Description page of Project Settings.


#include "ExtendableEntity.h"

#include "TrackGameMode.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AExtendableEntity::AExtendableEntity()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	
	StartCapComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StartCap"));
	EndCapComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EndCap"));
}

// Called when the game starts or when spawned
void AExtendableEntity::BeginPlay()
{
	Super::BeginPlay();

	if (const ATrackGameMode* TrackGameMode = Cast<ATrackGameMode>(GetWorld()->GetAuthGameMode()))
	{
		ClockHandle = TrackGameMode->QuartzClock;
	}
}

void AExtendableEntity::OnConstruction(const FTransform& Transform)
{
	if (!StartCapComponent || !EndCapComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("ExtendableEntity %s does not have start or end cap components, skipping construction."), *GetActorNameOrLabel());
	}
	StartCapComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	EndCapComponent->AttachToComponent(StartCapComponent, FAttachmentTransformRules::KeepRelativeTransform);
	
	StartCapComponent->SetStaticMesh(StartCapMesh);
	EndCapComponent->SetStaticMesh(EndCapMesh);

	StartCapComponent->SetMaterial(0, StartCapMaterial);
	EndCapComponent->SetMaterial(0, EndCapMaterial);

	EndCapComponent->SetRelativeLocation(FVector(-1, 0, 0) * Speed * NumBeats);

	const FRotator Rotator = FRotator(45 * static_cast<int>(Direction), 0, 0);
	StartCapComponent->SetRelativeRotation(Rotator);
}

// Called every frame
void AExtendableEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ClockHandle)
	{
		const FQuartzTransportTimeStamp Timestamp = ClockHandle->GetCurrentTimestamp(GetWorld());
		const float BeatFraction = ClockHandle->GetBeatProgressPercent();
		
		float BeatOffset = (Timestamp.Bars - 1) * 4 + (Timestamp.Beat - TargetBeat);
		if (!UseDiscreteMotion)
		{
			BeatOffset += BeatFraction;
			if (BeatFraction < Timestamp.BeatFraction)
			{
				BeatOffset += 1;
			}
		}
		
		SetActorLocation(GetActorForwardVector() * Speed * BeatOffset);
	}
}


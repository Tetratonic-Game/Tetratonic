// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCollider.h"

#include "PlayerPawn.h"

// Sets default values for this component's properties
UPlayerCollider::UPlayerCollider()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = false;
}

void UPlayerCollider::BeginPlay()
{
	Super::BeginPlay();

	if (UPrimitiveComponent* CollisionMesh = Cast<UPrimitiveComponent>(GetAttachParent()))
	{
		CollisionMesh->SetGenerateOverlapEvents(true);
		CollisionMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
		if (bIsBeginOverlap)
		{
			CollisionMesh->OnComponentBeginOverlap.AddDynamic(this, &UPlayerCollider::OnBeginOverlap);
		}
		else
		{
			CollisionMesh->OnComponentEndOverlap.AddDynamic(this, &UPlayerCollider::OnEndOverlap);
		}
	}
	else
	{
		UE_LOG(
			LogTemp,
			Warning,
			TEXT("PlayerCollider on Actor %s was not attached to a PrimitiveComponent."),
			*GetOwner()->GetActorNameOrLabel());
	}
}

void UPlayerCollider::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPlayerCollider::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bCollided) return;
	
	if (APlayerPawn* Player = Cast<APlayerPawn>(OtherActor))
	{
		bCollided = true;
		Player->EvaluateTimingEvent(AccuracyScoreModifiers, AccuracyHealthModifiers, bIncreasesCombo, OverlappedComp->GetComponentLocation());
		OnPlayerCollision.Broadcast();
	}
}

void UPlayerCollider::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (bCollided) return;
	
	if (APlayerPawn* Player = Cast<APlayerPawn>(OtherActor))
	{
		bCollided = true;
		Player->EvaluateTimingEvent(AccuracyScoreModifiers, AccuracyHealthModifiers, bIncreasesCombo, OverlappedComp->GetComponentLocation());
		OnPlayerCollision.Broadcast();
	}
}

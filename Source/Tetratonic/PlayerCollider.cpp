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
		CollisionMesh->OnComponentBeginOverlap.AddDynamic(this, &UPlayerCollider::OnOverlapBegin);
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


void UPlayerCollider::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APlayerPawn* Player = Cast<APlayerPawn>(OtherActor))
	{
		Player->AddToScore(ScoreModifier);
		if (bResetsCombo)
		{
			Player->ResetCombo();
		}
		if (bIncreasesCombo)
		{
			Player->IncreaseCombo();
		}
		Player->AddToHealth(HealthModifier);
	}
}
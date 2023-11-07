// Fill out your copyright notice in the Description page of Project Settings.


#include "Collider.h"

#include "PlayerPawn.h"

// Sets default values for this component's properties
UCollider::UCollider()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UCollider::BeginPlay()
{
	Super::BeginPlay();

	UStaticMeshComponent* Mesh = GetOwner()->FindComponentByClass<UStaticMeshComponent>();
	if (Mesh)
	{
		Mesh->SetGenerateOverlapEvents(true);
		Mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
		Mesh->OnComponentBeginOverlap.AddDynamic(this, &UCollider::OnOverlapBegin);
	}
	else
	{
		UE_LOG(
			LogTemp,
			Warning,
			TEXT("Actor %s was instantiated with a Collider but does not have a StaticMeshComponent."),
			*GetOwner()->GetActorNameOrLabel());
	}
	
}


void UCollider::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APlayerPawn* Player = Cast<APlayerPawn>(OtherActor))
	{
		Player->SetScore(Player->GetScore() + ScoreModifier);
	}
}




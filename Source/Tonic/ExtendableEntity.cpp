// Fill out your copyright notice in the Description page of Project Settings.


#include "ExtendableEntity.h"
#include "SubobjectDataFactory.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AExtendableEntity::AExtendableEntity()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	
	StartCapComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StartCap"));
	EndCapComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EndCap"));
}

// Called when the game starts or when spawned
void AExtendableEntity::BeginPlay()
{
	Super::BeginPlay();
}

void AExtendableEntity::OnConstruction(const FTransform& Transform)
{
	if (!StartCapComponent || !EndCapComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("ExtendableEntity %s does not have start or end cap components, skipping construction."), *GetActorNameOrLabel());
	}
	StartCapComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	EndCapComponent->AttachToComponent(StartCapComponent, FAttachmentTransformRules::KeepRelativeTransform);

	StartCapMesh->SetMaterial(0, StartCapMaterial);
	EndCapMesh->SetMaterial(0, EndCapMaterial);

	StartCapComponent->SetStaticMesh(StartCapMesh);
	EndCapComponent->SetStaticMesh(EndCapMesh);

	EndCapComponent->SetRelativeLocation(FVector(-1, 0, 0) * Length);
}


// Called every frame
void AExtendableEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


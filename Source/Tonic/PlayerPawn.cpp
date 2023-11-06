// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPawn.h"
#include "CoreMinimal.h"
#include "EnhancedInputSubsystems.h"

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

	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);	
		}
	}
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerPawn::DisplaceCharacter(const FVector NormalizedDirection)
{
	//UE_LOG(LogTemp, Display, TEXT("Called DisplaceCharacter"));
	const float InputDisplacement = 100.0f;
	const FVector Origin = FVector(0.0f, 0.0f, 1.0f);

	UStaticMeshComponent* PlayerMesh = GetPlayerMesh();
	//UE_LOG(LogTemp, Display, TEXT("%s"), *PlayerMesh->GetName());
	PlayerMesh->SetRelativeLocation((NormalizedDirection * InputDisplacement) + Origin);
}

void APlayerPawn::ReturnToOrigin()
{
	//UE_LOG(LogTemp, Display, TEXT("Called ReturnToOrigin"));
	const FVector Origin = FVector(0.0f, 0.0f, 1.0f);

	UStaticMeshComponent* PlayerMesh = GetPlayerMesh();
	PlayerMesh->SetRelativeLocation(Origin);
}

UStaticMeshComponent* APlayerPawn::GetPlayerMesh() const
{
	UStaticMeshComponent* PlayerMesh = FindComponentByClass<UStaticMeshComponent>();
	
	return PlayerMesh;
}




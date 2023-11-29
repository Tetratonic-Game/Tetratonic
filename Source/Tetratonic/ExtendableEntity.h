// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TrackGameMode.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Quartz/AudioMixerClockHandle.h"
#include "ExtendableEntity.generated.h"

UENUM(BlueprintType)
enum class EEntityDirection : uint8
{
	Right UMETA(DisplayName="Right"),
	TopRight UMETA(DisplayName="Top Right"),
	Top UMETA(DisplayName="Top"),
	TopLeft UMETA(DisplayName="Top Left"),
	Left UMETA(DisplayName="Left"),
	BottomLeft UMETA(DisplayName="Bottom Left"),
	Bottom UMETA(DisplayName="Bottom"),
	BottomRight UMETA(DisplayName="Bottom Right")
};

UENUM(BlueprintType)
enum class EEntityTarget : uint8
{
	Center UMETA(DisplayName="Center"),
	Top UMETA(DisplayName="Top"),
	Left UMETA(DisplayName="Left"),
	Bottom UMETA(DisplayName="Bottom"),
	Right UMETA(DisplayName="Right")
};


UCLASS()
class TETRATONIC_API AExtendableEntity : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExtendableEntity();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform & Transform) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UStaticMesh* StartCapMesh;

	UPROPERTY(EditAnywhere)
	UStaticMesh* EndCapMesh;

	UPROPERTY(EditAnywhere)
	UMaterialInstance* StartCapMaterial;

	UPROPERTY(EditAnywhere)
	UMaterialInstance* EndCapMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	EEntityDirection Direction = EEntityDirection::Right;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	EEntityTarget TargetPosition = EEntityTarget::Center;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	int32 TargetBeat = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	float NumBeats = 4;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	float Speed = 100;

	UPROPERTY(EditDefaultsOnly)
	bool UseDiscreteMotion = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 SpannerHealthModifier = -10;
	
	UPROPERTY(BlueprintReadOnly)
	UStaticMeshComponent* StartCapComponent;

	UPROPERTY(BlueprintReadOnly)
	UStaticMeshComponent* EndCapComponent;

	UPROPERTY(BlueprintReadOnly)
	UBoxComponent* SpannerCollisionComponent;

private:
	UPROPERTY()
	UQuartzClockHandle* ClockHandle;

	UPROPERTY()
	ATrackGameMode* TrackGameMode;

	FVector TargetPositionOffset;

};

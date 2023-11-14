// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExtendableEntity.generated.h"

UENUM(BlueprintType)
enum class EEntityDirection : uint8
{
	Top UMETA(DisplayName="Top"),
	Left UMETA(DisplayName="Left"),
	Right UMETA(DisplayName="Right"),
	Bottom UMETA(DisplayName="Bottom"),
	TopLeft UMETA(DisplayName="Top Left"),
	TopRight UMETA(DisplayName="Top Right"),
	BottomLeft UMETA(DisplayName="Bottom Left"),
	BottomRight UMETA(DisplayName="Bottom Right")
};

UCLASS()
class TONIC_API AExtendableEntity : public AActor
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
	int32 Length = 200;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	EEntityDirection Direction = EEntityDirection::Right;
	
	UPROPERTY(BlueprintReadWrite)
	UStaticMeshComponent* StartCapComponent;

	UPROPERTY(BlueprintReadWrite)
	UStaticMeshComponent* EndCapComponent;

};

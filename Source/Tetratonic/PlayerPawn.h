// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class TETRATONIC_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void DisplacePawn(const FVector NormalizedDirection);

	UFUNCTION(BlueprintCallable)
	void ReturnToOrigin();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	int32 GetScore() const;

	UFUNCTION(BlueprintCallable)
	void SetScore(const int32 NewScore);

	UPROPERTY(BlueprintReadWrite)
	float InputDisplacement;

private:
	UStaticMeshComponent* GetPlayerMesh() const;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* UpAction;

	UPROPERTY(EditAnywhere)
	int32 StartingScore = 100;

	UPROPERTY(EditAnywhere)
	FVector OriginPosition = FVector(0, 0, 0);
	
	int32 Score;
};

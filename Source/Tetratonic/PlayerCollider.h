// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PlayerCollider.generated.h"


UCLASS( DefaultToInstanced, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TETRATONIC_API UPlayerCollider : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerCollider();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(EditDefaultsOnly)
	int32 ScoreModifier = 0;

	UPROPERTY(EditDefaultsOnly)
	int32 HealthModifier = 0;

	UPROPERTY(EditDefaultsOnly)
	bool bResetsCombo;

	UPROPERTY(EditDefaultsOnly)
	bool bIncreasesCombo;

private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};

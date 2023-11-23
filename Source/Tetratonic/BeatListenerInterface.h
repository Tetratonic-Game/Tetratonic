// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BeatListenerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBeatListenerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TETRATONIC_API IBeatListenerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnBeat(FName ClockName, EQuartzCommandQuantization QuantizationType, int32 NumBars, int32 Beat, float BeatFraction);
};

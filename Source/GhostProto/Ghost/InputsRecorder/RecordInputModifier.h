// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputModifiers.h"
#include "EnhancedPlayerInput.h"
#include "InputActionValue.h"
#include "RecordInputModifier.generated.h"

/**
 * 
 */
UCLASS()
class GHOSTPROTO_API URecordInputModifier : public UInputModifier
{
	GENERATED_BODY()


	virtual FInputActionValue ModifyRaw_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue CurrentValue, float DeltaTime)
	{

		return CurrentValue;
	}
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "EnhancedPlayerInput.h"
#include "InputSave.generated.h"

/**
 * 
 */
UCLASS()
class GHOSTPROTO_API UInputSave : public USaveGame
{
	GENERATED_BODY()
	


public:
	UPROPERTY(EditAnywhere)
	TMap<float, UEnhancedPlayerInput*> inputMapping;




};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "AIController.h"
#include "GhostController.generated.h"

/**
 * 
 */
UCLASS()
class GHOSTPROTO_API AGhostController : public AAIController
{
	GENERATED_BODY()


	FRotator RotationInput;
	
	virtual void AddYawInput(float _value);
	virtual void AddPitchInput(float _value);
	void UpdateRotation(float _deltaTime);

};

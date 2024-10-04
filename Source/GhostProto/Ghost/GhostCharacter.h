// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../GhostProtoCharacter.h"
#include "InputAction.h"
#include "GhostCharacter.generated.h"



UCLASS()
class GHOSTPROTO_API AGhostCharacter : public AGhostProtoCharacter
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
public:

	///inject input inj character,
	void InjectInput(float _time, const FString& _name, const FInputActionValue& _value, const FRotator& _rotation);
	void LookController(const FInputActionValue& _value);

};

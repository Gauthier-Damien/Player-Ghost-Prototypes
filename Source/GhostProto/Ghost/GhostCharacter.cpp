// Fill out your copyright notice in the Description page of Project Settings.


#include "../Ghost/GhostCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFrameWork/SpringArmComponent.h"

void AGhostCharacter::BeginPlay()
{
	Super::BeginPlay();


}

void AGhostCharacter::InjectInput(float _time, const FString& _name, const FInputActionValue& _value, const FRotator& _rotation)
{
	Controller->SetControlRotation(_rotation);

	if (_name == "IA_Jump")
		Jump();
	if (_name == "IA_Move")
		Move(_value);
}


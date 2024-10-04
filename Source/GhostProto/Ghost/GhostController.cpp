// Fill out your copyright notice in the Description page of Project Settings.


#include "../Ghost/GhostController.h"
#include "IXRTrackingSystem.h"
#include "IXRCamera.h"
#include "IXRInput.h"

void AGhostController::AddYawInput(float _value)
{
	RotationInput.Yaw += !IsLookInputIgnored() ? _value * (1.0f) : 0.0f;
}

void AGhostController::AddPitchInput(float _value)
{
	RotationInput.Pitch += !IsLookInputIgnored() ? _value * (1.0f) : 0.0f;
}


void AGhostController::UpdateRotation(float _deltaTime)
{

}
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "CheckPoint.generated.h"


UCLASS()
class GHOSTPROTO_API ACheckPoint : public ATriggerBox
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
public:

	ACheckPoint();
	UFUNCTION()
	void OnOverlapBegin(class AActor* _overlappedActor, class AActor* _otherActor);

};

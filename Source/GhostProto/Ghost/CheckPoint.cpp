// Fill out your copyright notice in the Description page of Project Settings.


#include "../Ghost/CheckPoint.h"

ACheckPoint::ACheckPoint()
{
	OnActorBeginOverlap.AddDynamic(this, &ACheckPoint::OnOverlapBegin);
}

void ACheckPoint::OnOverlapBegin(AActor* _overlappedActor, AActor* _otherActor)
{


}



void ACheckPoint::BeginPlay()
{

	Super::BeginPlay();
}

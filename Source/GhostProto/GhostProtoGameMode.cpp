// Copyright Epic Games, Inc. All Rights Reserved.

#include "GhostProtoGameMode.h"
#include "GhostProtoCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGhostProtoGameMode::AGhostProtoGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

// Copyright Epic Games, Inc. All Rights Reserved.

#include "DodgeOfProjectilesGameMode.h"
#include "DodgeOfProjectilesCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADodgeOfProjectilesGameMode::ADodgeOfProjectilesGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectileTestGameMode.h"
#include "Character/ProjectileTestCharacter.h"

AProjectileTestGameMode::AProjectileTestGameMode()
{
	// Set default pawn class to our character
	DefaultPawnClass = AProjectileTestCharacter::StaticClass();	
}

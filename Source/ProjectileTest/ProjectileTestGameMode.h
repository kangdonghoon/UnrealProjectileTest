// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ProjectileTestGameMode.generated.h"

/**
 * The GameMode defines the game being played. It governs the game rules, scoring, what actors
 * are allowed to exist in this game type, and who may enter the game.
 *
 * This game mode just sets the default pawn to be the MyCharacter asset, which is a subclass of ProjectileTestCharacter
 */
UCLASS(minimalapi)
class AProjectileTestGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	AProjectileTestGameMode();
};

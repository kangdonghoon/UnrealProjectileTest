// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.h"
#include "NormalProjectile.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTILETEST_API ANormalProjectile : public AProjectileBase
{
	GENERATED_BODY()
	
protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick( float DeltaTime ) override;
};

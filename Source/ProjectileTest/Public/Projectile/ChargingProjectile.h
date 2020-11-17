// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.h"
#include "ChargingProjectile.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTILETEST_API AChargingProjectile : public AProjectileBase
{
	GENERATED_BODY()


public :

	AChargingProjectile();

private:

	float ProjectileScaleRate ;

public:

	virtual void InitProjectile() override ;
	
};

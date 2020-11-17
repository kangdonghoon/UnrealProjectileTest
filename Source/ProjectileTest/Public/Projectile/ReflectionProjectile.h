// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.h"
#include "ReflectionProjectile.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTILETEST_API AReflectionProjectile : public AProjectileBase
{
	GENERATED_BODY()

public:

	AReflectionProjectile();

private:

	FLinearColor ArrowColor;

protected:

	/**발사체가 충돌시 반대방향으로 진행방향 변경*/
	void ReflectProjectile(const FVector& NewDirection );

	virtual void OnHitEvent( const FHitResult& HitResult ) override;

public:

	virtual void InitProjectile() override;

};

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

	/**�߻�ü�� �浹�� �ݴ�������� ������� ����*/
	void ReflectProjectile(const FVector& NewDirection );

	virtual void OnHitEvent( const FHitResult& HitResult ) override;

public:

	virtual void InitProjectile() override;

};

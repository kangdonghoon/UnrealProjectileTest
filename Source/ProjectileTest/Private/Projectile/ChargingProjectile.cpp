// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/ChargingProjectile.h"

AChargingProjectile::AChargingProjectile()
{

	ProjectileScaleRate = 3.0f;
}

void AChargingProjectile::InitProjectile()
{
	Super::InitProjectile();

	//발사체 Scale를 ProjectileScaleRate 만큼 증가 시킴
	SetActorScale3D( GetActorScale() * ProjectileScaleRate );
}
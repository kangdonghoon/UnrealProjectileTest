// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/ChargingProjectile.h"

AChargingProjectile::AChargingProjectile()
{

	ProjectileScaleRate = 3.0f;
}

void AChargingProjectile::InitProjectile()
{
	Super::InitProjectile();

	//�߻�ü Scale�� ProjectileScaleRate ��ŭ ���� ��Ŵ
	SetActorScale3D( GetActorScale() * ProjectileScaleRate );
}
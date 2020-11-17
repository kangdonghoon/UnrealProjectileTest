// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/ReflectionProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/ArrowComponent.h"

AReflectionProjectile::AReflectionProjectile()
{
	ArrowColor = FLinearColor::Blue;
}

void AReflectionProjectile::ReflectProjectile( const FVector & NewDirection )
{
	MovementComp->SetUpdatedComponent(RootComponent);
	MovementComp->Velocity = ProjectileSpeed * NewDirection;
	MovementComp->UpdateComponentVelocity();
}

void AReflectionProjectile::OnHitEvent( const FHitResult& HitResult )
{
	ReflectProjectile( GetActorForwardVector()*-1 );
}

void AReflectionProjectile::InitProjectile()
{
	Super::InitProjectile();

	//ArrowComp »ö º¯°æ
	ArrowComp->SetArrowColor( ArrowColor );
}

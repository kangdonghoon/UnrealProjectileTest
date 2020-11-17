/// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile/SeperationProjectile.h"
#include "Components/ArrowComponent.h"
#include "Projectile/ProjectileSpawnerComponent.h"
#include "Character/ProjectileTestCharacter.h"



ASeperationProjectile::ASeperationProjectile()
{
}

void ASeperationProjectile::Destroyed()
{
	SpawnProjectileAtArrows();

	Super::Destroyed();
}

UArrowComponent* ASeperationProjectile::AddArrowComponet( float Angle )
{
	UArrowComponent* NewArrowComp = NewObject<UArrowComponent>( this  );

	if ( NewArrowComp == nullptr ) return nullptr;
	
	NewArrowComp->RegisterComponent();

	NewArrowComp->AttachToComponent( RootComponent , FAttachmentTransformRules::KeepRelativeTransform );

	NewArrowComp->SetRelativeRotation( FRotator( Angle , 0.0f , 0.0f ) );

	NewArrowComp->SetHiddenInGame( false );

	AttachedArrows.Add( NewArrowComp );

	return NewArrowComp;
}

void ASeperationProjectile::InitProjectile()
{
	Super::InitProjectile();

	// �������� 45����ŭ ������ �����Ͽ� ����
	AttachedArrows.Add( ArrowComp );
	AddArrowComponet(  45.0f );
	AddArrowComponet( -45.0f );

	AProjectileTestCharacter* PlayerCharacter = Cast<AProjectileTestCharacter>( GetInstigator() );

	if( PlayerCharacter != nullptr)
	{
		ProjectileSpawner = PlayerCharacter->GetProjectileSpawnerComponent();
	}
}

void ASeperationProjectile::SpawnProjectileAtArrows()
{
	if ( ProjectileSpawner.IsValid() == false ) return;

	//Arrow ������ŭ ���ο� �߻�ü ����
	for( UArrowComponent* Arrow : AttachedArrows )
	{
		if ( Arrow == nullptr ) continue;

		FProjectileSpawnData NewSpawnData;

		NewSpawnData.Direction = Arrow->GetForwardVector();
		NewSpawnData.SpawnLocation = Arrow->GetComponentLocation();
		NewSpawnData.SpawnType = EProjectileSpawnType::ENormal;

		ProjectileSpawner->SpawnProjectile( NewSpawnData );
	}
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ProjectileSpawnCountWidget.h"
#include "Projectile/ProjectileSpawnerComponent.h"
#include "Character/ProjectileTestCharacter.h"


void UProjectileSpawnCountWidget::NativeConstruct()
{
	AProjectileTestCharacter* PlayerCharacter = Cast<AProjectileTestCharacter>( GetOwningPlayerPawn() );

	if ( PlayerCharacter != nullptr )
	{
		if ( PlayerCharacter->GetProjectileSpawnerComponent() != nullptr )
		{
			PlayerCharacter->GetProjectileSpawnerComponent()->SpawnProjectileTypeCallback.BindLambda
			( [ this ]( const EProjectileSpawnType& SpawnType ) { UpdateSpawnCount( SpawnType ); } );
		}
	}else
	{
		RemoveFromParent();
	}
}

void UProjectileSpawnCountWidget::UpdateAllSpawnCountUI()
{
	UpdateSpawnCountUI( EProjectileSpawnType::ENormal );
	UpdateSpawnCountUI( EProjectileSpawnType::ECharging );
	UpdateSpawnCountUI( EProjectileSpawnType::ESeperation );
	UpdateSpawnCountUI( EProjectileSpawnType::EReflection );
}

void UProjectileSpawnCountWidget::ResetAllSpawnCount()
{
	NormalProjectileCount     = 0;
	ChargingProjectileCount   = 0;
	SeperationProjectileCount = 0;
	RefelctionProjectileCount = 0;

	UpdateAllSpawnCountUI();
}

void UProjectileSpawnCountWidget::UpdateSpawnCount( const EProjectileSpawnType& SpawnType )
{
	switch ( SpawnType )
	{
	case EProjectileSpawnType::ENormal:
		{
			NormalProjectileCount++;
		}
		break;
	case EProjectileSpawnType::ECharging:
		{
			ChargingProjectileCount++;
		}
		break;
	case EProjectileSpawnType::ESeperation:
		{
			SeperationProjectileCount++;
		}
		break;
	case EProjectileSpawnType::EReflection:
		{
			RefelctionProjectileCount++;
		}
		break;
	}

	UpdateSpawnCountUI( SpawnType );
}


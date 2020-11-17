// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/ProjectileSpawnerComponent.h"
#include "Projectile/ProjectileBase.h"
#include "Projectile/NormalProjectile.h"
#include "Projectile/ChargingProjectile.h"
#include "Projectile/SeperationProjectile.h"
#include "Projectile/ReflectionProjectile.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UProjectileSpawnerComponent::UProjectileSpawnerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void UProjectileSpawnerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UProjectileSpawnerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UProjectileSpawnerComponent::SpawnProjectile( const FProjectileSpawnData& SpawnData )
{
	TSubclassOf<class AProjectileBase> ProjectileClass = nullptr;

	FTransform SpawnTransform( SpawnData.SpawnRotation , SpawnData.SpawnLocation );

	FActorSpawnParameters SpawnParam;
	SpawnParam.Owner = GetOwner();

	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	switch ( SpawnData.SpawnType )
	{
	case EProjectileSpawnType::ENormal :
		{
			ProjectileClass = ANormalProjectile::StaticClass();
		}
		break;
	case EProjectileSpawnType::ECharging :
		{
			ProjectileClass = AChargingProjectile::StaticClass();
		}
		break;
	case EProjectileSpawnType::ESeperation :
		{
			ProjectileClass = ASeperationProjectile::StaticClass();
		}
		break;
	case EProjectileSpawnType::EReflection :
		{
			ProjectileClass = AReflectionProjectile::StaticClass();
		}
		break;
	default:
		{
			ProjectileClass = ANormalProjectile::StaticClass();
		}
		break;
	}
	UWorld* World = GetWorld();

	if(World != nullptr)
	{
		UE_LOG( LogTemp , Warning , TEXT( "SpawnProjectileStart" ) );

		AProjectileBase* Projectile = World->SpawnActorDeferred<AProjectileBase>( ProjectileClass , SpawnTransform );
		if( Projectile != nullptr)
		{
		Projectile->SetOwner( GetOwner() );

		Projectile->SetInstigator( Cast<APawn>( GetOwner() ));

		Projectile->SetProjectileDirection( SpawnData.Direction );

		Projectile->InitProjectile();

		Projectile->FinishSpawning( SpawnTransform );

		SpawnProjectileTypeCallback.ExecuteIfBound( SpawnData.SpawnType );

		}
	}
}

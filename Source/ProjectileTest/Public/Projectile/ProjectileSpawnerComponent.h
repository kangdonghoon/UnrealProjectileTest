// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProjectileSpawnerComponent.generated.h"

/** 발사체 생성 타입 enum */
UENUM( BlueprintType )
enum class EProjectileSpawnType : uint8
{
	ENormal ,
	ECharging ,
	ESeperation ,
	EReflection
};
/**발사체 생성 Data Struct*/
USTRUCT()
struct FProjectileSpawnData
{
	GENERATED_BODY()

	EProjectileSpawnType SpawnType;
	
	FVector SpawnLocation;

	FRotator SpawnRotation;

	FVector Direction;

	FProjectileSpawnData() :
	  SpawnType( EProjectileSpawnType::ENormal ) 
    , SpawnLocation( FVector( 0.0f , 0.0f , 0.0f ) )
	, SpawnRotation( FRotator(0.0f,0.0f,0.0f))
	, Direction(FVector(0.0f,0.0f,0.0f))
	{
	};
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTILETEST_API UProjectileSpawnerComponent : public UActorComponent
{
	GENERATED_BODY()

	DECLARE_DELEGATE_OneParam( FSpawnProjectileDelegate , const EProjectileSpawnType& );

public:
	
	// Sets default values for this component's properties
	UProjectileSpawnerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	/** 발사체가 생성되면 호출되는 Callback Delegate */
	FSpawnProjectileDelegate SpawnProjectileTypeCallback;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**발사체의 생성정보를 받아 발사체를 생성 */
	void SpawnProjectile( const FProjectileSpawnData& SpawnData );
};

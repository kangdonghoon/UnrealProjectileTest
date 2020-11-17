// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Projectile/ProjectileSpawnerComponent.h"
#include "ProjectileSpawnCountWidget.generated.h"
/**
 * 
 */
UCLASS()
class PROJECTILETEST_API UProjectileSpawnCountWidget : public UUserWidget
{
	GENERATED_BODY()

private:

	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , meta = ( AllowPrivateAccess = "true" ) )
	int32 NormalProjectileCount     = 0;

	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , meta = ( AllowPrivateAccess = "true" ) )
	int32 ChargingProjectileCount   = 0;

	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , meta = ( AllowPrivateAccess = "true" ) )
	int32 SeperationProjectileCount = 0;

	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , meta = ( AllowPrivateAccess = "true" ) )
	int32 RefelctionProjectileCount = 0;

public:

	/** 상속받은 BP Widget에게 해상 SpawnType의 CountTextUI를 갱신 */
	UFUNCTION( BlueprintImplementableEvent)
	void UpdateSpawnCountUI( const EProjectileSpawnType& SpawnType );

	/** 상속받은 BP Widget에게 모든 Type의 CountTextUI 초기화 */
	UFUNCTION( BlueprintCallable )
	void ResetAllSpawnCount();

	/** 상속받은 BP Widget에게 모든 SpawnType의 CountTextUI를 갱신 */
	void UpdateAllSpawnCountUI();

	/** PlayerCharacter의 SpawnProjectileComp의 SpawnCallBackDelegate와 Binding */
	void UpdateSpawnCount( const EProjectileSpawnType& SpawnType );

	virtual void NativeConstruct() override;
	
};

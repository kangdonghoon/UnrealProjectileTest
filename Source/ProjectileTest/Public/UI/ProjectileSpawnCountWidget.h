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

	/** ��ӹ��� BP Widget���� �ػ� SpawnType�� CountTextUI�� ���� */
	UFUNCTION( BlueprintImplementableEvent)
	void UpdateSpawnCountUI( const EProjectileSpawnType& SpawnType );

	/** ��ӹ��� BP Widget���� ��� Type�� CountTextUI �ʱ�ȭ */
	UFUNCTION( BlueprintCallable )
	void ResetAllSpawnCount();

	/** ��ӹ��� BP Widget���� ��� SpawnType�� CountTextUI�� ���� */
	void UpdateAllSpawnCountUI();

	/** PlayerCharacter�� SpawnProjectileComp�� SpawnCallBackDelegate�� Binding */
	void UpdateSpawnCount( const EProjectileSpawnType& SpawnType );

	virtual void NativeConstruct() override;
	
};

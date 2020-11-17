// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.h"
#include "SeperationProjectile.generated.h"
/**
 * 
 */
UCLASS()
class PROJECTILETEST_API ASeperationProjectile : public AProjectileBase
{
	GENERATED_BODY()
	
public:

	ASeperationProjectile();

protected:
	/** ���ο� �߻�ü�� ������ ArrowComp Array*/
	UPROPERTY( VisibleDefaultsOnly , Category = Projectile )
	TArray<class UArrowComponent*> AttachedArrows;
	
	/** �÷��̾��� ProjectileSpawner ���۷��� */
	UPROPERTY()
	TWeakObjectPtr< class UProjectileSpawnerComponent> ProjectileSpawner;

	/** ���ο� ArrowCompoent �� �߰� 
	*
	* @param Angle ���� ��ŭ �����̼� ���� ����
	*/
	UArrowComponent* AddArrowComponet( float Angle );

	/** ���ο� �߻�ü�� Arrow ��ġ�� ���� */
	void SpawnProjectileAtArrows();

	virtual void Destroyed() override;

public :
 
	virtual void InitProjectile() override;

};

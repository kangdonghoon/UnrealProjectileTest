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
	/** 새로운 발사체가 생성될 ArrowComp Array*/
	UPROPERTY( VisibleDefaultsOnly , Category = Projectile )
	TArray<class UArrowComponent*> AttachedArrows;
	
	/** 플레이어의 ProjectileSpawner 레퍼런싱 */
	UPROPERTY()
	TWeakObjectPtr< class UProjectileSpawnerComponent> ProjectileSpawner;

	/** 새로운 ArrowCompoent 를 추가 
	*
	* @param Angle 각도 만큼 로테이션 변경 생성
	*/
	UArrowComponent* AddArrowComponet( float Angle );

	/** 새로운 발사체를 Arrow 위치에 생성 */
	void SpawnProjectileAtArrows();

	virtual void Destroyed() override;

public :
 
	virtual void InitProjectile() override;

};

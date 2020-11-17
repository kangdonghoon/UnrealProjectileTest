// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

UCLASS()
class PROJECTILETEST_API AProjectileBase : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AProjectileBase();

protected:

	/** 발사체 콜리전 */
	UPROPERTY( VisibleDefaultsOnly , Category = Projectile )
	class USphereComponent* CollisionComp;

	/** 발사체 mesh */
	UPROPERTY( VisibleDefaultsOnly , Category = Projectile )
	class UStaticMeshComponent* StaticMeshComp;

	/** 발사체의 movement component*/
	UPROPERTY( VisibleDefaultsOnly , Category = Projectile )
	class UProjectileMovementComponent* MovementComp;

	/** 발사체의 이동 방향 arrow component*/
	UPROPERTY( VisibleDefaultsOnly , Category = Projectile )
	class UArrowComponent* ArrowComp;

	/**발사체의 속력*/
	float ProjectileSpeed;
	float LifeTime;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Destroyed() override;

	/** 발사체의 CollisionComponent에 충돌이 생기면 HitResult 정보를 받음 */
	UFUNCTION()
	virtual void OnHitEvent(const FHitResult& HitResult );

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** 발사체 생성 초기 세팅 로직을 실행 하위 발사체에서 override 해서 사용*/
	virtual void InitProjectile();

	/** 발사체의 진행 방향을 설정*/
	void SetProjectileDirection( FVector Direction );

	FORCEINLINE class UProjectileMovementComponent* GetMovementComponent() { return MovementComp; };

};

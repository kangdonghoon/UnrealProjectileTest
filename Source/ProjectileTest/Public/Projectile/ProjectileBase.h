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

	/** �߻�ü �ݸ��� */
	UPROPERTY( VisibleDefaultsOnly , Category = Projectile )
	class USphereComponent* CollisionComp;

	/** �߻�ü mesh */
	UPROPERTY( VisibleDefaultsOnly , Category = Projectile )
	class UStaticMeshComponent* StaticMeshComp;

	/** �߻�ü�� movement component*/
	UPROPERTY( VisibleDefaultsOnly , Category = Projectile )
	class UProjectileMovementComponent* MovementComp;

	/** �߻�ü�� �̵� ���� arrow component*/
	UPROPERTY( VisibleDefaultsOnly , Category = Projectile )
	class UArrowComponent* ArrowComp;

	/**�߻�ü�� �ӷ�*/
	float ProjectileSpeed;
	float LifeTime;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Destroyed() override;

	/** �߻�ü�� CollisionComponent�� �浹�� ����� HitResult ������ ���� */
	UFUNCTION()
	virtual void OnHitEvent(const FHitResult& HitResult );

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** �߻�ü ���� �ʱ� ���� ������ ���� ���� �߻�ü���� override �ؼ� ���*/
	virtual void InitProjectile();

	/** �߻�ü�� ���� ������ ����*/
	void SetProjectileDirection( FVector Direction );

	FORCEINLINE class UProjectileMovementComponent* GetMovementComponent() { return MovementComp; };

};

// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/ProjectileBase.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionComp = CreateDefaultSubobject<USphereComponent>( TEXT( "SphereComponent" ) );
	CollisionComp->InitSphereRadius( 15.0f );
	CollisionComp->bTraceComplexOnMove = true;
	CollisionComp->SetCollisionEnabled( ECollisionEnabled::QueryOnly );
	// Projectile용 콜리전 타입 생성  == ECC_GameTraceChannel2
	CollisionComp->SetCollisionObjectType( ECollisionChannel::ECC_GameTraceChannel2 );
	CollisionComp->SetCollisionResponseToAllChannels( ECR_Ignore );
	CollisionComp->SetCollisionResponseToChannel( ECC_WorldStatic , ECR_Block );
	CollisionComp->SetCollisionResponseToChannel( ECC_WorldDynamic , ECR_Block );
	CollisionComp->SetCollisionResponseToChannel( ECC_Pawn , ECR_Block );
	CollisionComp->SetCollisionResponseToChannel( ECollisionChannel::ECC_EngineTraceChannel1 , ECR_Ignore );
	RootComponent = CollisionComp;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "StaticMeshComponent" ) );
	StaticMeshComp->SetCollisionEnabled( ECollisionEnabled::NoCollision );
	StaticMeshComp->SetRelativeScale3D( FVector(0.3f , 0.3f , 0.3f));
	StaticMeshComp->SetRelativeLocation( FVector( 0.0f , 0.0f , CollisionComp->GetScaledSphereRadius()*-1 ) );
	StaticMeshComp->SetupAttachment( RootComponent );

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshFinder( TEXT( "StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'" ) );
	if(MeshFinder.Succeeded() == true)
	{
		StaticMeshComp->SetStaticMesh( MeshFinder.Object );
	}

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>( TEXT( "ProjectileMovementComponent" ) );
	MovementComp->UpdatedComponent = CollisionComp;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->ProjectileGravityScale = 0.f;
	MovementComp->OnProjectileStop.AddDynamic( this , &AProjectileBase::OnHitEvent );

	ArrowComp = CreateDefaultSubobject<UArrowComponent>( TEXT( "ArrowComponent" ) );
	ArrowComp->SetupAttachment( RootComponent );
	ArrowComp->SetVisibility( true );
	ArrowComp->SetHiddenInGame( false );

	ProjectileSpeed = 100.0f;
	LifeTime = 3.0f;
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG( LogTemp , Warning , TEXT( "SpawnProjectile : %s" ) , *GetName() );

}
void AProjectileBase::Destroyed()
{
	Super::Destroyed();

	UE_LOG( LogTemp , Warning , TEXT( "ProejectileDestroyed : %s" ) , *GetName() );

}

void AProjectileBase::OnHitEvent( const FHitResult& HitResult )
{
	UE_LOG( LogTemp , Warning , TEXT( " Hit OtherActor : %s" ) , *HitResult.Actor->GetName() );

	if ( IsValid(this) == true && IsPendingKill() != true )
	{
		Destroy();
	}
}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectileBase::SetProjectileDirection( FVector Direction )
{
	MovementComp->Velocity =  Direction * ProjectileSpeed;
}

void AProjectileBase::InitProjectile()
{
	SetLifeSpan( LifeTime );
}


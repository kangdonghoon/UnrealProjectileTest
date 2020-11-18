// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "Character/ProjectileTestCharacter.h"
#include "PaperFlipbookComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraComponent.h"
#include "TimerManager.h"
#include "Projectile/ProjectileSpawnerComponent.h"
#include "UI/WidgetManagerComponent.h"

//#include "Kismet/KismetMathLibrary.h"

DEFINE_LOG_CATEGORY_STATIC( SideScrollerCharacter , Log , All );

//////////////////////////////////////////////////////////////////////////
// AProjectileTestCharacter

AProjectileTestCharacter::AProjectileTestCharacter()
{

	// Use only Yaw from the controller and ignore the rest of the rotation.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Set the size of our collision capsule.
	GetCapsuleComponent()->SetCapsuleHalfHeight( 96.0f );
	GetCapsuleComponent()->SetCapsuleRadius( 40.0f );
	//OwnerPawn 용 콜리전 타입 생성  == ECC_GameTraceChannel2
	GetCapsuleComponent()->SetCollisionObjectType( ECollisionChannel::ECC_GameTraceChannel2 );

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>( TEXT( "CameraBoom" ) );
	CameraBoom->SetupAttachment( RootComponent );
	CameraBoom->TargetArmLength = 500.0f;
	CameraBoom->SocketOffset = FVector( 0.0f , 0.0f , 75.0f );
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->SetRelativeRotation (FRotator( 0.0f , -90.0f , 0.0f ));


	// Create an orthographic camera (no perspective) and attach it to the boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>( TEXT( "SideViewCamera" ) );
	SideViewCameraComponent->ProjectionMode = ECameraProjectionMode::Orthographic;
	SideViewCameraComponent->OrthoWidth = 2048.0f;
	SideViewCameraComponent->SetupAttachment( CameraBoom , USpringArmComponent::SocketName );

	// Prevent all automatic rotation behavior on the camera, character, and camera component
	CameraBoom->SetUsingAbsoluteRotation(true);
	SideViewCameraComponent->bUsePawnControlRotation = false;
	SideViewCameraComponent->bAutoActivate = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	// Configure character movement
	GetCharacterMovement()->GravityScale = 2.0f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.0f;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	GetCharacterMovement()->MaxFlySpeed = 600.0f;

	// Lock character motion onto the XZ plane, so the character can't move in or out of the screen
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintNormal( FVector( 0.0f , -1.0f , 0.0f ) );

	// Behave like a traditional 2D platformer character, with a flat bottom instead of a curved capsule bottom
	// Note: This can cause a little floating when going up inclines; you can choose the tradeoff between better
	// behavior on the edge of a ledge versus inclines by setting this to true or false
	GetCharacterMovement()->bUseFlatBaseForFloorChecks = true;

	// 	TextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("IncarGear"));
	// 	TextComponent->SetRelativeScale3D(FVector(3.0f, 3.0f, 3.0f));
	// 	TextComponent->SetRelativeLocation(FVector(35.0f, 5.0f, 20.0f));
	// 	TextComponent->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	// 	TextComponent->SetupAttachment(RootComponent);

	// Enable replication on the Sprite component so animations show up when networked
	GetSprite()->SetIsReplicated( false );
	bReplicates = false;

	ProjectileSpawner = CreateDefaultSubobject<UProjectileSpawnerComponent>( TEXT( "ProjectileSpawner" ) );

	//기준점에서 플레이어 앞 방향 20 위로 50 추가
	SpawnLocationOffset = FVector2D( 20.0f , 50.0f );

}

//////////////////////////////////////////////////////////////////////////
// Animation

void AProjectileTestCharacter::UpdateAnimation()
{
	const FVector PlayerVelocity = GetVelocity();
	const float PlayerSpeedSqr = PlayerVelocity.SizeSquared();

	// Are we moving or standing still?
	UPaperFlipbook* DesiredAnimation = ( PlayerSpeedSqr > 0.0f ) ? RunningAnimation : IdleAnimation;
	if ( GetSprite()->GetFlipbook() != DesiredAnimation )
	{
		GetSprite()->SetFlipbook( DesiredAnimation );
	}
}

void AProjectileTestCharacter::Tick( float DeltaSeconds )
{
	Super::Tick( DeltaSeconds );

	UpdateCharacter();
}

void AProjectileTestCharacter::BeginPlay()
{
	Super::BeginPlay();

	if ( IsLocallyControlled() == true )
	{
		WidgetManagerComp = NewObject<UWidgetManagerComponent>( this );
		if ( WidgetManagerComp != nullptr )
		{
			WidgetManagerComp->ReregisterComponent();

			WidgetManagerComp->ShowProjectileSpawnCountWidget();
		}
	}else
	{
		//LocalControll Player Character가 아니면 콜리전 타입 Pawn 설정
		GetCapsuleComponent()->SetCollisionObjectType( ECollisionChannel::ECC_Pawn );
	}
}

FProjectileSpawnData AProjectileTestCharacter::GetSpawnDataBySpawnType( const EProjectileSpawnType& SpawnType )
{
	FProjectileSpawnData SpawnData;
	SpawnData.SpawnLocation = GetProjectileSpawnLocation();
	SpawnData.Direction = GetActorForwardVector();
	SpawnData.SpawnType = SpawnType;

	return SpawnData;
}

const FVector AProjectileTestCharacter::GetProjectileSpawnLocation()
{
	FVector Location = GetCapsuleComponent()->GetComponentLocation();

	Location.Z = Location.Z - GetCapsuleComponent()->GetScaledCapsuleHalfHeight() + SpawnLocationOffset.Y;

	Location = Location + GetActorForwardVector() * SpawnLocationOffset.X;

	return Location;
}


//////////////////////////////////////////////////////////////////////////
// Input

void AProjectileTestCharacter::SetupPlayerInputComponent( class UInputComponent* PlayerInputComponent )
{
	// Note: the 'Jump' action and the 'MoveRight' axis are bound to actual keys/buttons/sticks in DefaultInput.ini (editable from Project Settings..Input)
	PlayerInputComponent->BindAction( "Jump" , IE_Pressed , this , &ACharacter::Jump );
	PlayerInputComponent->BindAction( "Jump" , IE_Released , this , &ACharacter::StopJumping );

	PlayerInputComponent->BindAction( "FirstFire" , IE_Pressed , this , &AProjectileTestCharacter::PressFirstFireInput );
	PlayerInputComponent->BindAction( "FirstFire" , IE_Released , this , &AProjectileTestCharacter::ReleasedFirstFireInput );

	PlayerInputComponent->BindAction( "SecondFire" , IE_Pressed , this , &AProjectileTestCharacter::PressSecondFireInput );
	PlayerInputComponent->BindAction( "SecondFire" , IE_Released , this , &AProjectileTestCharacter::ReleasedSecondFireInput );

	PlayerInputComponent->BindAxis( "MoveRight" , this , &AProjectileTestCharacter::MoveRight );

	PlayerInputComponent->BindTouch( IE_Pressed , this , &AProjectileTestCharacter::TouchStarted );
	PlayerInputComponent->BindTouch( IE_Released , this , &AProjectileTestCharacter::TouchStopped );
}

void AProjectileTestCharacter::MoveRight( float Value )
{
	/*UpdateChar();*/

	// Apply the input to the character motion
	AddMovementInput( FVector( 1.0f , 0.0f , 0.0f ) , Value );
}

void AProjectileTestCharacter::PressFirstFireInput()
{
	// 타이머 시작
	StartInputPressTimer();
}

void AProjectileTestCharacter::ReleasedFirstFireInput()
{
	if ( GetWorldTimerManager().IsTimerActive( InputPressTimeHandler ) == false ) return;

	EProjectileSpawnType NewProjectileSpawnType = EProjectileSpawnType::ENormal;

	if ( InpuPressTimePerSecond >= MaxInputPressSecond )
	{
		NewProjectileSpawnType = EProjectileSpawnType::ECharging;
	}
	else
	{
		NewProjectileSpawnType = EProjectileSpawnType::ENormal;
	}

	ProjectileSpawner->SpawnProjectile( GetSpawnDataBySpawnType( NewProjectileSpawnType ) );

	StopInputPressTimer();
}

void AProjectileTestCharacter::PressSecondFireInput()
{
	if ( GetWorldTimerManager().IsTimerActive( InputPressTimeHandler ) == true )
	{
		if ( InpuPressTimePerSecond < 1 )
		{
			EProjectileSpawnType NewProjectileSpawnType = EProjectileSpawnType::ESeperation;

			ProjectileSpawner->SpawnProjectile( GetSpawnDataBySpawnType( NewProjectileSpawnType ) );
		}
	}
}

void AProjectileTestCharacter::ReleasedSecondFireInput()
{
	EProjectileSpawnType NewProjectileSpawnType = EProjectileSpawnType::EReflection;

	ProjectileSpawner->SpawnProjectile( GetSpawnDataBySpawnType( NewProjectileSpawnType ) );
}


void AProjectileTestCharacter::TouchStarted( const ETouchIndex::Type FingerIndex , const FVector Location )
{
	// Jump on any touch
	Jump();
}

void AProjectileTestCharacter::TouchStopped( const ETouchIndex::Type FingerIndex , const FVector Location )
{
	// Cease jumping once touch stopped
	StopJumping();
}

//////////////////////////////////////////////////////////////////////////
// Input Timer
void AProjectileTestCharacter::StartInputPressTimer()
{
	if ( InputPressTimeHandler.IsValid() == true )
	{
		GetWorldTimerManager().UnPauseTimer( InputPressTimeHandler );
	}
	else
	{   // 1초마다 loop 되는 타이머 생성
		GetWorldTimerManager().SetTimer( InputPressTimeHandler , this , &AProjectileTestCharacter::CountInputPress , 1.0f , true , 1.0f );
	}
	// TimerWidget 추가
	if ( WidgetManagerComp != nullptr )
	{
		WidgetManagerComp->ShowChargingProgressWidget( MaxInputPressSecond );
	}
}

void AProjectileTestCharacter::StopInputPressTimer()
{
	if ( InputPressTimeHandler.IsValid() == true && GetWorldTimerManager().IsTimerActive( InputPressTimeHandler ) == true )
	{
		GetWorldTimerManager().PauseTimer( InputPressTimeHandler );

		InpuPressTimePerSecond = 0.f;
	}
	// TimerWidget 제거
	if ( WidgetManagerComp != nullptr )
	{
		WidgetManagerComp->HiddenChargingProgressWidget();
	}
}

void AProjectileTestCharacter::CountInputPress()
{
	if ( InpuPressTimePerSecond <= MaxInputPressSecond )
	{
		InpuPressTimePerSecond++;

		UE_LOG( LogTemp , Warning , TEXT( "ChargingTime : %d " ) , InpuPressTimePerSecond );
	}
}

void AProjectileTestCharacter::UpdateCharacter()
{
	// Update animation to match the motion
	UpdateAnimation();

	// Now setup the rotation of the controller based on the direction we are travelling
	const FVector PlayerVelocity = GetVelocity();
	float TravelDirection = PlayerVelocity.X;
	// Set the rotation so that the character faces his direction of travel.
	if ( Controller != nullptr )
	{
		if ( TravelDirection < 0.0f )
		{
			Controller->SetControlRotation( FRotator( 0.0 , 180.0f , 0.0f ) );
		}
		else if ( TravelDirection > 0.0f )
		{
			Controller->SetControlRotation( FRotator( 0.0f , 0.0f , 0.0f ) );
		}
	}
}

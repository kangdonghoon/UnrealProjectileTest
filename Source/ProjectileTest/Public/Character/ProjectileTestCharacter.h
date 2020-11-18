// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "ProjectileTestCharacter.generated.h"

class UTextRenderComponent;

/**
 * This class is the default character for ProjectileTest, and it is responsible for all
 * physical interaction between the player and the world.
 *
 * The capsule component (inherited from ACharacter) handles collision with the world
 * The CharacterMovementComponent (inherited from ACharacter) handles movement of the collision capsule
 * The Sprite component (inherited from APaperCharacter) handles the visuals
 */

enum class EProjectileSpawnType : uint8;

UCLASS(config=Game)
class AProjectileTestCharacter : public APaperCharacter
{
	GENERATED_BODY()

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera, meta=(AllowPrivateAccess="true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** 입력별 프로젝타일 생성을 처리*/
	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , meta = ( AllowPrivateAccess = "true" ) )
	class UProjectileSpawnerComponent* ProjectileSpawner;

	/** 위젯 관리 */
	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , meta = ( AllowPrivateAccess = "true" ) )
	class UWidgetManagerComponent* WidgetManagerComp;

	UTextRenderComponent* TextComponent;

private:

	/** 키를 입력했을때 최대 저장 second 변수 */
	static const uint8 MaxInputPressSecond = 3;

	/** 현재 입력키를 눌렀을때 저장되는 second 변수*/
	uint8 InpuPressTimePerSecond = 0;

	/** 입력을 카운트하는 타이머 핸들 변수*/
	FTimerHandle InputPressTimeHandler;

	/** 발사체 타입에따른 스폰 data 리턴*/
	struct FProjectileSpawnData GetSpawnDataBySpawnType( const EProjectileSpawnType& SpawnType );

	/** 캐릭터 기준 프로젝타일 생성하는 위치 반환 */
	const FVector GetProjectileSpawnLocation();

protected:
	// The animation to play while running around
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Animations)
	class UPaperFlipbook* RunningAnimation;

	// The animation to play while idle (standing still)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* IdleAnimation;

	/** 생성 기준점에 생성 offset 값을 추가 적용 */
	FVector2D SpawnLocationOffset;

	/** Called to choose the correct animation to play based on the character's movement state */
	void UpdateAnimation();

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 첫번째 프로젝타일 생성 버튼를 눌렀을때 실행 바인딩 함수 */
	void PressFirstFireInput();

	/** 첫번째 프로젝타일 생성 버튼를 땠을때 실행 바인딩 함수 */
	void ReleasedFirstFireInput();

	/** 두번째 프로젝타일 생성 버튼를 눌렀을때 실행 바인딩 함수 */
	void PressSecondFireInput();

	/** 두번 프로젝타일 생성 버튼을 땠을때 실행 바인딩 함수 */
	void ReleasedSecondFireInput();

	void UpdateCharacter();

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** 입력 타이머 시작*/
	void StartInputPressTimer();

	/** 입력 타이머 멈춤*/
	void StopInputPressTimer();

	/** 입력 타이머가 Loop를 돌면서 시간 초를 count*/
	void CountInputPress();

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

	virtual void Tick( float DeltaSeconds ) override;

	virtual void BeginPlay() override;

public:

	AProjectileTestCharacter();

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns Projectile Spawner subobject **/
	FORCEINLINE class UProjectileSpawnerComponent* GetProjectileSpawnerComponent() const { return ProjectileSpawner; }
};

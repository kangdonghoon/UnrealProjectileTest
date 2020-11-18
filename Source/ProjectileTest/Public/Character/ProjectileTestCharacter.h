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

	/** �Էº� ������Ÿ�� ������ ó��*/
	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , meta = ( AllowPrivateAccess = "true" ) )
	class UProjectileSpawnerComponent* ProjectileSpawner;

	/** ���� ���� */
	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , meta = ( AllowPrivateAccess = "true" ) )
	class UWidgetManagerComponent* WidgetManagerComp;

	UTextRenderComponent* TextComponent;

private:

	/** Ű�� �Է������� �ִ� ���� second ���� */
	static const uint8 MaxInputPressSecond = 3;

	/** ���� �Է�Ű�� �������� ����Ǵ� second ����*/
	uint8 InpuPressTimePerSecond = 0;

	/** �Է��� ī��Ʈ�ϴ� Ÿ�̸� �ڵ� ����*/
	FTimerHandle InputPressTimeHandler;

	/** �߻�ü Ÿ�Կ����� ���� data ����*/
	struct FProjectileSpawnData GetSpawnDataBySpawnType( const EProjectileSpawnType& SpawnType );

	/** ĳ���� ���� ������Ÿ�� �����ϴ� ��ġ ��ȯ */
	const FVector GetProjectileSpawnLocation();

protected:
	// The animation to play while running around
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Animations)
	class UPaperFlipbook* RunningAnimation;

	// The animation to play while idle (standing still)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* IdleAnimation;

	/** ���� �������� ���� offset ���� �߰� ���� */
	FVector2D SpawnLocationOffset;

	/** Called to choose the correct animation to play based on the character's movement state */
	void UpdateAnimation();

	/** Called for side to side input */
	void MoveRight(float Value);

	/** ù��° ������Ÿ�� ���� ��ư�� �������� ���� ���ε� �Լ� */
	void PressFirstFireInput();

	/** ù��° ������Ÿ�� ���� ��ư�� ������ ���� ���ε� �Լ� */
	void ReleasedFirstFireInput();

	/** �ι�° ������Ÿ�� ���� ��ư�� �������� ���� ���ε� �Լ� */
	void PressSecondFireInput();

	/** �ι� ������Ÿ�� ���� ��ư�� ������ ���� ���ε� �Լ� */
	void ReleasedSecondFireInput();

	void UpdateCharacter();

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** �Է� Ÿ�̸� ����*/
	void StartInputPressTimer();

	/** �Է� Ÿ�̸� ����*/
	void StopInputPressTimer();

	/** �Է� Ÿ�̸Ӱ� Loop�� ���鼭 �ð� �ʸ� count*/
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

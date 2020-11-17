// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "ChargingProgressWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTILETEST_API UChargingProgressWidget : public UUserWidget
{
	GENERATED_BODY()

private:

	bool bChargingStart;

	/** 현재 충전 초 */
	float CurrentChargingSecond;
	
	/** 목표치 충전 초 */
	float MaxChargingSecond;

public:

	virtual void NativeConstruct() override;

	virtual void NativeTick( const FGeometry& MyGeometry , float DeltaTime ) override;
	
	/** MaxChargingSecond 설정 및 Second Count Start*/
	void StartProgressBarCharging( const uint8& TargetSecond );

	void InitWidget();


protected:

	/** BP Widget에서 화면에 표시될 프로그레스바와 Binding */
	UFUNCTION(BlueprintPure )
	float GetProgressBarRate();

	/** 위젯이 활성화면 틱에서 DeltaTime을 받아 CurrentChargingSecond을 갱신 */
	void AddProgressBarRate( float Deltatime );
};

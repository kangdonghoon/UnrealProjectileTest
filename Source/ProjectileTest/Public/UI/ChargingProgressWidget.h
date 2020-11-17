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

	/** ���� ���� �� */
	float CurrentChargingSecond;
	
	/** ��ǥġ ���� �� */
	float MaxChargingSecond;

public:

	virtual void NativeConstruct() override;

	virtual void NativeTick( const FGeometry& MyGeometry , float DeltaTime ) override;
	
	/** MaxChargingSecond ���� �� Second Count Start*/
	void StartProgressBarCharging( const uint8& TargetSecond );

	void InitWidget();


protected:

	/** BP Widget���� ȭ�鿡 ǥ�õ� ���α׷����ٿ� Binding */
	UFUNCTION(BlueprintPure )
	float GetProgressBarRate();

	/** ������ Ȱ��ȭ�� ƽ���� DeltaTime�� �޾� CurrentChargingSecond�� ���� */
	void AddProgressBarRate( float Deltatime );
};

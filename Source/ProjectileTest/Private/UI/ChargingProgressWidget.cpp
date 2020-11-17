// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ChargingProgressWidget.h"


void UChargingProgressWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UE_LOG( LogTemp , Warning , TEXT( "ChargingProgressWidget Contstruct()") );

	InitWidget();
}

void UChargingProgressWidget::NativeTick( const FGeometry& MyGeometry , float DeltaTime )
{
	Super::NativeTick( MyGeometry , DeltaTime );

	if ( bChargingStart == true )
	{
		AddProgressBarRate( DeltaTime );
	}
}

void UChargingProgressWidget::StartProgressBarCharging( const uint8& TargetSecond )
{
	MaxChargingSecond = TargetSecond;
	bChargingStart = true;
}

void UChargingProgressWidget::InitWidget()
{
	bChargingStart = false;
	CurrentChargingSecond = 0.0f;
	MaxChargingSecond = 0.0f;
}

float UChargingProgressWidget::GetProgressBarRate()
{
	if ( bChargingStart == false ) return 0.0f;

	return FMath::Clamp( CurrentChargingSecond / MaxChargingSecond ,0.0f ,1.0f);
}

void UChargingProgressWidget::AddProgressBarRate( float Deltatime )
{
	CurrentChargingSecond += Deltatime;
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WidgetManagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTILETEST_API UWidgetManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWidgetManagerComponent();

private:
	/** Blueprint ChargingWidgetClass 저장 */
	TSubclassOf<class UUserWidget> BP_ChargingWidgetClass;

	/** Blueprint SpawnCountWidgetClass 저장 */
	TSubclassOf<class UUserWidget> BP_SpawnCountWidgetClass;

	/** 생성된 ChargingWidget 저장 */
	UPROPERTY()
	class UChargingProgressWidget* ChargingProgressWidget;

	/** 생성된 ProjectileSpawnCountWidget 저장 */
	UPROPERTY()
	class UProjectileSpawnCountWidget* ProjectileSpawnCountWidget;

	/** widget 생성이 안되있으면 생성하고 아니면 기존의 Charging Widget Return */
	class UChargingProgressWidget* GetChargingProgressWidget();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** 인풋을 누르면 ChargingWidget 뷰포트에 추가 
	*
	* @Param TargetSecond Charging 게이지의 목표 값
	*/
	void ShowChargingProgressWidget( const uint8& TargetSecond );

	/** 인풋을 때면 ChargingWidget 뷰포트에서 제거 */
	void HiddenChargingProgressWidget();

	/** 발사체 생성 카운트 Widget 뷰포트에 추가*/
	void ShowProjectileSpawnCountWidget();
		
};

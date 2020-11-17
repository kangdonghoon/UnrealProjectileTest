// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetManagerComponent.h"
#include "Blueprint/UserWidget.h"
#include "UI/ChargingProgressWidget.h"
#include "UI/ProjectileSpawnCountWidget.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values for this component's properties
UWidgetManagerComponent::UWidgetManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	
	 ConstructorHelpers::FClassFinder<UUserWidget> ChargingWidgetFinder( TEXT( "/Game/BP_ChargingProgressBarWidget.BP_ChargingProgressBarWidget_C" ) );
	if(ChargingWidgetFinder.Succeeded() == true && ChargingWidgetFinder.Class != nullptr )
	{
		BP_ChargingWidgetClass = ChargingWidgetFinder.Class;
	}

	 ConstructorHelpers::FClassFinder<UUserWidget> SpawnCountWidgetFinder( TEXT( "/Game/BP_ProjectileSpawnCountWidget.BP_ProjectileSpawnCountWidget_C") );
	if ( SpawnCountWidgetFinder.Succeeded() == true && SpawnCountWidgetFinder.Class != nullptr )
	{
		BP_SpawnCountWidgetClass = SpawnCountWidgetFinder.Class;
	}		
	// ...

	ChargingProgressWidget = nullptr;

	ProjectileSpawnCountWidget = nullptr;

	
}

// Called when the game starts
void UWidgetManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

// Called every frame
void UWidgetManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UWidgetManagerComponent::ShowChargingProgressWidget( const uint8& TargetSecond )
{
	if ( GetChargingProgressWidget() == nullptr ) return;

	GetChargingProgressWidget()->AddToViewport();

	GetChargingProgressWidget()->StartProgressBarCharging( TargetSecond );
}

void UWidgetManagerComponent::HiddenChargingProgressWidget()
{
	if ( GetChargingProgressWidget() == nullptr ) return;

	GetChargingProgressWidget()->RemoveFromViewport();
}

void UWidgetManagerComponent::ShowProjectileSpawnCountWidget()
{
	if ( GetOwner() == nullptr ) return;

	if ( ProjectileSpawnCountWidget == nullptr )
	{
		ProjectileSpawnCountWidget = CreateWidget<UProjectileSpawnCountWidget>( GetWorld() , BP_SpawnCountWidgetClass );

		if ( ProjectileSpawnCountWidget != nullptr )
		{
			ProjectileSpawnCountWidget->AddToViewport();;
		}
		else
		{
			return;
		}
	}
}


UChargingProgressWidget* UWidgetManagerComponent::GetChargingProgressWidget()
{
	if ( GetOwner() == nullptr ) return nullptr;

	if( ChargingProgressWidget == nullptr)
	{
		ChargingProgressWidget = CreateWidget<UChargingProgressWidget>( GetWorld() , BP_ChargingWidgetClass);
		
		if ( ChargingProgressWidget != nullptr )
		{
			return ChargingProgressWidget;
		}
		else
		{
			return nullptr;
		}
	}

	return ChargingProgressWidget;
}


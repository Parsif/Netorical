// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Engine/DataTable.h"

#include "SEventManager.generated.h"

UENUM(BlueprintType)
enum class EEventType : uint8
{
	LOCAL		UMETA(DisplayName = "Local"),
	REGION		UMETA(DisplayName = "Region"),
	GLOBAL		UMETA(DisplayName = "Global"),
	STAT		UMETA(DisplayName = "Stat")
};

USTRUCT(BlueprintType)
struct FEventDataTable : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		EEventType Type;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString Title;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString Location;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<FString> Preconditions;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString Effect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString EffectDescription;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NETORICAL_API USEventManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USEventManager();

private:
	// DataTable of Events
	UDataTable* EventsDataTable;
	// Timer for local events
	FTimerHandle LocalTimer;
	// Timer for region events
	FTimerHandle RegionTimer;
	// Timer for global and state events
	FTimerHandle GlobalTimer;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void CallEvent();

	//Timer Controlls
	void StartTimer(FTimerHandle &Timer, void (USEventManager::*InTimeMethod)(), float MinDelay, float MaxDelay);
	void PauseTimer(FTimerHandle &Timer);
	void UnPauseTimer(FTimerHandle& Timer);
	void ClearTimer(FTimerHandle &Timer);
	void RestartTimer(FTimerHandle &Timer, void (USEventManager::* InTimeMethod)(), float MinDelay, float MaxDelay);

private:
	bool EventCannotBeCalled(int32);
};

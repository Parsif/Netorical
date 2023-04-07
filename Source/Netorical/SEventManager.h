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
	const float MinEventTimerDelay = 1.0f; // 300.0f
	const float MaxEventTimerDelay = 1.0f; // 900.0f


	UDataTable* EventsDataTable;
	FTimerHandle EventTimerManager;



public:	
	void PushEvent(FString EventID);
	bool EventCannotBeCalled(int32);
	
	//Timer Controlls
	void StartTimer(FTimerHandle &Timer, void (USEventManager::*InTimeMethod)(), float MinDelay, float MaxDelay);
	void PauseTimer(FTimerHandle &Timer);
	void UnPauseTimer(FTimerHandle& Timer);
	void ClearTimer(FTimerHandle &Timer);
	void RestartTimer(FTimerHandle &Timer, void (USEventManager::* InTimeMethod)(), float MinDelay, float MaxDelay);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void PublishEvent();

private:
	bool CheckEventPreconditions(FString EventID);
};

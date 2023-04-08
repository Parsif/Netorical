// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Misc/DateTime.h"

#include "SWorldTime.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NETORICAL_API USWorldTime : public UActorComponent
{
	GENERATED_BODY()

protected:
	const FString WorldFirstDay = TEXT("1973-04-01");
	FString LoadDate = TEXT("1999-04-01");
	float DayLenght = 20.0f;

public:	
	// Sets default values for this component's properties
	USWorldTime();
	void SetLoadDate(FString ISODate);
	FString Now();

private:
	FDateTime WorldTime;
	FTimerHandle WorldTImeTimerHandle;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void NextDay();
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "SEventManager.h"

// Sets default values for this component's properties
USEventManager::USEventManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	//load events data from datatable
	static ConstructorHelpers::FObjectFinder<UDataTable> EventsDataTable_Object(TEXT("DataTable'/Game/DataTable/Events_DataTable.Events_DataTable'"));
	if (EventsDataTable_Object.Succeeded())
	{
		EventsDataTable = EventsDataTable_Object.Object;
	}
}

// Called when the game starts
void USEventManager::BeginPlay()
{
	Super::BeginPlay();

	USEventManager::StartTimer(EventTimerManager, &USEventManager::PublishEvent, MinEventTimerDelay, MaxEventTimerDelay);
}

// Event publising methods
void USEventManager::PublishEvent()
{
	FString SelectedEventName;

	do {
		int32 RandomEvent = FMath::RandRange(0, EventsDataTable->GetRowNames().GetAllocatedSize() / EventsDataTable->GetRowNames().GetTypeSize() - 1);
		SelectedEventName = EventsDataTable->GetRowNames()[RandomEvent].ToString();
	} while (CheckEventPreconditions(SelectedEventName) != true);

	/*                                    
	
	There will be call Event logic
	
	*/

	USEventManager::StartTimer(EventTimerManager, &USEventManager::PublishEvent, MinEventTimerDelay, MaxEventTimerDelay);
}

void USEventManager::PushEvent(FString EventID)
{
	FEventDataTable* Event = EventsDataTable->FindRow<FEventDataTable>(*FString(EventID), TEXT("GENERAL"));

	if (Event == nullptr)
	{
		return;
	}

	// there will be call event logic
}

//Event precondition method for uncallable event
bool USEventManager::EventCannotBePublised(int32 Number)
{
	return false;
}

bool USEventManager::CheckEventPreconditions(FString EventID)
{
	// there will be check precondition logic
	return true;
}

//Timers controlls
void USEventManager::StartTimer(FTimerHandle& Timer, void (USEventManager::*InTimeMethod)(), float MinDelay, float MaxDelay)
{
	if (GetWorld()->GetTimerManager().IsTimerPending(Timer))
		return;

	float RandomTimerDelay = FMath::RandRange(MinDelay, MaxDelay);
	GetWorld()->GetTimerManager().SetTimer(Timer, this, InTimeMethod, RandomTimerDelay);
}

void USEventManager::PauseTimer(FTimerHandle& Timer)
{
	if (GetWorld()->GetTimerManager().IsTimerPaused(Timer))
		return;

	GetWorld()->GetTimerManager().PauseTimer(Timer);
}

void USEventManager::UnPauseTimer(FTimerHandle& Timer)
{
	if (GetWorld()->GetTimerManager().IsTimerActive(Timer))
		return;

	GetWorld()->GetTimerManager().UnPauseTimer(Timer);
}

void USEventManager::ClearTimer(FTimerHandle& Timer)
{
	if (!GetWorld()->GetTimerManager().TimerExists(Timer))
		return;

	GetWorld()->GetTimerManager().ClearTimer(Timer);
}

void USEventManager::RestartTimer(FTimerHandle& Timer, void (USEventManager::* InTimeMethod)(), float MinDelay, float MaxDelay)
{
	if (GetWorld()->GetTimerManager().TimerExists(Timer))
		USEventManager::ClearTimer(Timer);

	USEventManager::StartTimer(Timer, InTimeMethod, MinDelay, MaxDelay);
}
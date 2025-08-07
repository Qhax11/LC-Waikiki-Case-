// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Managers/S_UIManager.h"
#include "Gameplay/Managers/S_PuzzleManager.h"
#include "Gameplay/Managers/DS_UIManager.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Gameplay/UI/W_EndScreen.h"

void US_UIManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	Collection.InitializeDependency(US_PuzzleManager::StaticClass());

	DS_UIManager = GetDefault<UDS_UIManager>();
	if (!DS_UIManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("DS_UIManager is null in %s"), *this->GetName());
		return;
	}

	US_PuzzleManager* S_PuzzleManager = GetGameInstance()->GetSubsystem<US_PuzzleManager>();
	if (!S_PuzzleManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("S_PuzzleManager is null in: %s"), *GetName());
		return;
	}

	S_PuzzleManager->OnPuzzleCompleted.AddDynamic(this, &US_UIManager::OnPuzzleCompleted);
}

void US_UIManager::OnPuzzleCompleted(const FGameStats& GameStats)
{
	CreateEndScreenWidget(GameStats);
}

void US_UIManager::CreateEndScreenWidget(const FGameStats& GameStats)
{
	if (!DS_UIManager)
	{
		UE_LOG(LogTemp, Error, TEXT("DS_UIManager is null"));
		return;
	}

	APlayerController* PC = GetGameInstance()->GetWorld()->GetFirstPlayerController();

	UUserWidget* Widget = UWidgetBlueprintLibrary::Create(GetGameInstance()->GetWorld(), DS_UIManager->W_EndScreen.LoadSynchronous(), PC);
	UW_EndScreen* W_EndScreen = Cast<UW_EndScreen>(Widget);
	if (W_EndScreen)
	{
		W_EndScreen->AddToViewport();
		W_EndScreen->InitalizeEndScreen(GameStats);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No valid PlayerController found"));
	}
}






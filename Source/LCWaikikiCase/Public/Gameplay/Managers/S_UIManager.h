// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Subsystems/GameInstanceSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "S_UIManager.generated.h"

/**
 * US_UIManager
 *
 * UI Manager Subsystem responsible for managing high-level UI logic during gameplay.
 *
 * Works in combination with the UDS_UIManager developer settings class
 * for configurable widget references.
 */

UCLASS()
class LCWAIKIKICASE_API US_UIManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION()
	void OnPuzzleCompleted(const FGameStats& GameStats);

	void CreateEndScreenWidget(const FGameStats& GameStats);

	const class UDS_UIManager* DS_UIManager;
};

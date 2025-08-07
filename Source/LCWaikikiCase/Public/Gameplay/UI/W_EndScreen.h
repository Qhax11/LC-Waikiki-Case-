// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "W_EndScreen.generated.h"

struct FGameStats;

/**
 * UW_EndScreen
 *
 * UI widget displayed when a puzzle is completed.
 *
 * This widget is spawned by the UI Manager and initialized with gameplay stats.
 */

UCLASS()
class LCWAIKIKICASE_API UW_EndScreen : public UUserWidget
{
	GENERATED_BODY()

public:
	/**
    * Initializes the end screen widget with the given game stats.
    *
    * This function is called by the UI Manager after the widget is created,
    * and is responsible for passing data (e.g., move count, time taken, etc.) to the UI elements for display.
    */
	void InitializeEndScreen(const FGameStats& GameStats);

	/**
	 * Blueprint event for initializing the end screen UI.
	 *
	 * Called from InitalizeEndScreen in C++ to allow Blueprint-based visual setup.
	 */
	UFUNCTION(BlueprintImplementableEvent)
	void BP_InitializeEndScreen(const FGameStats& GameStats);
};

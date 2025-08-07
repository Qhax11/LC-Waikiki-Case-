// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DeveloperSettings.h"
#include "DS_UIManager.generated.h"

/**
 * UDS_UIManager
 *
 * Developer settings class for managing UI-related configurations.
 * This class holds configurable references to UI widgets used in the project, such as the End Screen widget.
 * 
 * Can be configured from Project Settings under:
 * Project Settings → Project Systems | Subsystems | UIManager
 */

class UW_PuzzlePieceBase;
class UW_EndScreen;

UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "Project Systems | Subsystems | UIManager"))
class LCWAIKIKICASE_API UDS_UIManager : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	/** Puzzle piece widget classes shown in the puzzle container. */
	UPROPERTY(EditAnywhere, Config)
	TArray<TSoftClassPtr<UW_PuzzlePieceBase>> PuzzlePieceWidgetClasses;

	UPROPERTY(EditAnywhere, Config)
	TSoftClassPtr<UW_EndScreen> W_EndScreen;
};

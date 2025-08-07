// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DeveloperSettings.h"
#include "Gameplay/UI/W_PuzzlePieceBase.h"
#include "Gameplay/Actors/PuzzlePiece/PuzzlePieceBase.h"
#include "Gameplay/Actors/PuzzlePiece/PuzzlePieceSlotBase.h"
#include "DS_PuzzleManager.generated.h"

/**
 * Defines a mapping between a puzzle piece class and its target slot.
 * Used by the puzzle manager to track correct piece-slot assignments.
 */
USTRUCT(BlueprintType)
struct FPuzzleMapping
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSoftClassPtr<UW_PuzzlePieceBase> PieceWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<APuzzlePieceBase> PieceClass;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<APuzzlePieceSlotBase> PieceTargetSlot;
};

/**
 * Developer Settings class for defining default puzzle piece-slot mappings.
 * 
 * Can be configured from Project Settings under:
 * Project Settings → Project Systems | Subsystems | PuzzleManager
 * 
 */
UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "Project Systems | Subsystems | PuzzleManager"))
class LCWAIKIKICASE_API UDS_PuzzleManager : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	// List of expected piece-slot assignments that define the correct solution
	UPROPERTY(EditAnywhere, Config)
	TArray<FPuzzleMapping> PuzzleMap;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "W_PuzzlePieceBase.generated.h"


/**
 * UW_PuzzlePieceBase
 *
 * Base class for all puzzle piece widgets used in the UI.
 *
 * This class serves as the foundation for specific puzzle piece types
 * and can be extended to add functionality like drag-and-drop behavior,
 * visual state changes, or interaction events.
 */
UCLASS()
class LCWAIKIKICASE_API UW_PuzzlePieceBase : public UUserWidget
{
	GENERATED_BODY()
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PuzzlePieceSlotBase.generated.h"

class APuzzlePieceBase;

USTRUCT(BlueprintType)
struct FPuzzleSlotState
{
    GENERATED_BODY()

private:
    UPROPERTY()
    APuzzlePieceBase* CurrentPiece = nullptr;

    UPROPERTY()
    bool bIsEmpty = true;

    UPROPERTY()
    bool bHasCorrectPiece = false;

public:
    APuzzlePieceBase* GetCurrentPiece() const { return CurrentPiece; }
    void SetCurrentPiece(APuzzlePieceBase* NewPiece)
    {
        CurrentPiece = NewPiece;
        bIsEmpty = (NewPiece == nullptr);
    }

    bool IsEmpty() const { return bIsEmpty; }
    void SetIsEmpty(bool bEmpty) { bIsEmpty = bEmpty; }

    bool HasCorrectPiece() const { return bHasCorrectPiece; }
    void SetHasCorrectPiece(bool bCorrect) { bHasCorrectPiece = bCorrect; }
};

/**
 * Represents a slot in the puzzle where a puzzle piece can be placed.
 *
 * This class holds the current piece reference and information about whether
 * the slot is empty or has the correct piece. It also contains visual and
 * transform components to define the puzzle slot's location and appearance.
 */

UCLASS()
class LCWAIKIKICASE_API APuzzlePieceSlotBase : public AActor
{
	GENERATED_BODY()
	
public:	
	APuzzlePieceSlotBase();

	/** Returns the world location where the puzzle piece should be spawned or placed */
	FVector GetPiecePlacementPointLocation();

    FPuzzleSlotState& GetSlotState() { return SlotState; }
    void UpdateSlotState(const FPuzzleSlotState& NewState)
    {
        SlotState = NewState;
    }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PuzzlePieceSlotBase")
	UStaticMeshComponent* SMC_PuzzlePieceSlotBase;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* PiecePlacementPoint;

private:
    FPuzzleSlotState SlotState;
};

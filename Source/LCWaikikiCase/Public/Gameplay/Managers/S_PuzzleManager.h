// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Subsystems/GameInstanceSubsystem.h"
#include "Gameplay/Managers/DS_PuzzleManager.h"
#include "S_PuzzleManager.generated.h"

/**
 * Struct to hold gameplay stats such as move count and time
 */
USTRUCT(BlueprintType)
struct FGameStats
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	int32 MoveCount;

	UPROPERTY(BlueprintReadOnly)
	int32 Time;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPuzzleCompleted, const FGameStats&, GameStats);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMoveCountUpdated, int32, MoveCount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimeUpdated, int32, Time);


/**
 * Subsystem that manages puzzle logic, moves, and completion tracking.
 */
UCLASS()
class LCWAIKIKICASE_API US_PuzzleManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	void StartTimer();

	/** Called every second to update elapsed time */
	void UpdateTime();

public:
	/**
    * Called when a puzzle piece widget is dropped on a slot from the UI.
    * Triggered by BPW_PuzzlePieceBase logic (e.g., drag & drop operation in the puzzle UI).
    */
	UFUNCTION(BlueprintCallable)
	void HandleDropPuzzlePieceWidgetOnSlot(TSubclassOf<UW_PuzzlePieceBase> WidgetClass, APuzzlePieceSlotBase* Slot);

	/**
    * Called when the player picks up a 3D puzzle piece in the world.
    * Triggered by BP_PlayerController logic during drag interaction.
    */
	UFUNCTION(BlueprintCallable)
	void HandleDragPuzzlePiece(APuzzlePieceBase* Piece);

	/**
    * Called when the player drops a 3D puzzle piece on a slot in the world.
    * Triggered by BP_PlayerController logic after completing a drag interaction.
    */
	UFUNCTION(BlueprintCallable)
	void HandleDropPuzzlePiece(APuzzlePieceBase* Piece, AActor* TargetActor);

	UPROPERTY(BlueprintAssignable)
	FOnPuzzleCompleted OnPuzzleCompleted;

	UPROPERTY(BlueprintAssignable)
	FOnMoveCountUpdated OnMoveCountUpdated;

	UPROPERTY(BlueprintAssignable)
	FOnTimeUpdated OnTimeUpdated;

private:
	/**
    * Finds the puzzle piece class that corresponds to the given widget class.
    *
    * @param WidgetClass The widget class to find a matching puzzle piece class for.
    * @return The matching puzzle piece class if found; nullptr otherwise.
    */
	TSubclassOf<APuzzlePieceBase> FindPieceClassByWidget(TSubclassOf<UW_PuzzlePieceBase> WidgetClass) const;

	/**
    * Assigns a puzzle piece to a specified slot, updating both the slot and piece states.
    */
	void AssignPieceToSlot(APuzzlePieceBase* Piece, APuzzlePieceSlotBase* TargetSlot);

	void HandleMoveMade();

	/** Checks if the placement is correct */
	bool IsCorrectPlacement(TSubclassOf<APuzzlePieceBase> PieceClass, TSubclassOf<APuzzlePieceSlotBase> SlotClass);

	/**
    * Checks whether all slots in the puzzle map have their correct pieces assigned.
    * Returns true only if all mapped slots are correctly filled.
    */
	bool IsPuzzleCompleted() const;

	/** Called when the puzzle is completed */
	void PuzzleCompleted();

	/**
    * Enables or disables collision for all puzzle pieces.
    *
    * This is used to control trace detection from the camera perspective during drag operations.
    * When a trace hits a puzzle piece, we move that piece to the trace impact location.
    * To avoid the trace continuously hitting the same piece (which would block detecting the ground),
    * we disable collision on puzzle pieces right after a hit.
    *
    * This allows subsequent traces to pass through the piece and detect other surfaces (e.g., the ground).
    * Meanwhile, the puzzle piece itself handles internal updates (e.g., ticking to adjust position)
    * once placed.
    *
    * @param bEnable True to enable collision on puzzle pieces, false to disable.
    */
	void SetPuzzlePiecesCollision(bool bEnable);

	UPROPERTY()
	const class UDS_PuzzleManager* DS_PuzzleManager = nullptr;

	UPROPERTY()
	TArray<APuzzlePieceBase*> PuzzlePieceInstances;

	FTimerHandle TimerHandle;
	float Time = 0.0f;
	int32 MoveCount = 0;
};

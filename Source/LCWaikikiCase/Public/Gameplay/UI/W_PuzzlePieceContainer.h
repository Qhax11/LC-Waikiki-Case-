// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"
#include "W_PuzzlePieceContainer.generated.h"

class UW_PuzzlePieceBase;

/**
 * UW_PuzzlePieceContainer
 *
 * Widget responsible for displaying puzzle pieces in two vertical columns.
 *
 * On construction, it shuffles the puzzle pieces and distributes them evenly across two vertical boxes.
 */
UCLASS()
class LCWAIKIKICASE_API UW_PuzzlePieceContainer : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

private:
	/**
    * Loads puzzle piece widget classes from the developer settings into a local array.
    * Since the original developer settings array is treated as const (read-only),
    * this function creates a mutable copy to allow safe modifications like shuffling
    * without affecting the original config data.
    */
	void LoadPuzzlePiecesToLocal();

	/**
    * Randomly shuffles the given array of puzzle piece classes.
    * Uses Fisher–Yates shuffle algorithm to randomize order.
    */
	void ShuffleArrayManually(TArray<TSubclassOf<UW_PuzzlePieceBase>>& Array);

	/**
	 * Creates puzzle piece widgets from the shuffled array and adds them to the vertical boxes.
	 * Alternates between two columns to distribute pieces evenly.
	 */
	void CreatePiecesAndAddToVerticalBox();

	UW_PuzzlePieceBase* CreatePuzzlePiece(TSubclassOf<UW_PuzzlePieceBase> PuzzlePieceClass);

	void AddPuzzlePieceToVerticalBox(TObjectPtr<UVerticalBox> VerticalBox, UW_PuzzlePieceBase* PuzzlePiece);

	UPROPERTY()
	const class UDS_UIManager* DS_UIManager;

	UPROPERTY()
	TArray<TSubclassOf<UW_PuzzlePieceBase>> LocalPuzzlePieces;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UVerticalBox> VB_PuzzlePieces1;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UVerticalBox> VB_PuzzlePieces2;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UVerticalBox> VB_PuzzlePieces3;
};

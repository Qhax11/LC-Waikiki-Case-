// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PuzzlePieceBase.generated.h"

/**
 * APuzzlePieceBase is a simple actor that represents a draggable puzzle piece in the puzzle system.
 *
 * This class primarily holds references and state data related to the piece, such as:
 * - Whether it's currently being dragged
 * - Its assigned puzzle slot
 *
 */

UCLASS()
class LCWAIKIKICASE_API APuzzlePieceBase : public AActor
{
	GENERATED_BODY()
	
public:	
	APuzzlePieceBase();

	void SetCollisionEnabled();

	void SetCollisionDisabled();

	/** Blueprint event triggered when the piece starts dragging from a slot */
	/** Called from S_PazzleManager */
	UFUNCTION(BlueprintImplementableEvent)
	void BP_HandleDragFromSlotEvent();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_HandleDropFromSlotEvent();

	/** Reference to the slot this puzzle piece is currently occupying */
	UPROPERTY()
	class APuzzlePieceSlotBase* CurrentSlot = nullptr;

	/** Whether the puzzle piece is currently being dragged */
	UPROPERTY(BlueprintReadOnly)
	bool bOnDrag = false;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* SMC_PuzzlePiece;

};

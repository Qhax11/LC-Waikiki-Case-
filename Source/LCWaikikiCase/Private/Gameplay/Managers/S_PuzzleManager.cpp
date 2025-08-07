// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Managers/S_PuzzleManager.h"

void US_PuzzleManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	DS_PuzzleManager = GetDefault<UDS_PuzzleManager>();
	if (!DS_PuzzleManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("DS_PuzzleManager is null in %s"), *this->GetName());
		return;
	}

	StartTimer();
}

void US_PuzzleManager::StartTimer()
{
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle,
		this,
		&US_PuzzleManager::UpdateTime,
		1.0f,
		true
	);
}

void US_PuzzleManager::UpdateTime()
{
	Time++;
	OnTimeUpdated.Broadcast(Time);
}

void US_PuzzleManager::HandleDropPuzzlePieceWidgetOnSlot(TSubclassOf<UW_PuzzlePieceBase> WidgetClass, APuzzlePieceSlotBase* Slot)
{
	if (!Slot || !WidgetClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("Slot or PieceClass is null in %s"), *this->GetName());
		return;
	}

	TSubclassOf<APuzzlePieceBase> FindedPuzzlePieceClass = FindPieceClassByWidget(WidgetClass);
	if (!FindedPuzzlePieceClass) 
	{
		UE_LOG(LogTemp, Warning, TEXT("FindedPuzzlePieceClass is null in %s"), *this->GetName());
		return;
	}

	APuzzlePieceBase* NewPiece = GetWorld()->SpawnActor<APuzzlePieceBase>(FindedPuzzlePieceClass);
	if (!NewPiece)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to spawn puzzle piece in %s"), *GetName());
		return;
	}

	PuzzlePieceInstances.Add(NewPiece);

	AssignPieceToSlot(NewPiece, Slot);
	HandleMoveMade();
}

void US_PuzzleManager::HandleDragPuzzlePiece(APuzzlePieceBase* Piece)
{
	if (!Piece)
	{
		UE_LOG(LogTemp, Warning, TEXT("Piece is null in: %s!"), *GetName());
		return;
	}

	if (Piece->CurrentSlot)
	{
		Piece->CurrentSlot->GetSlotState().SetIsEmpty(true);
	}

	SetPuzzlePiecesCollision(false);
	Piece->bOnDrag = true;
	Piece->BP_HandleDragFromSlotEvent();
}

void US_PuzzleManager::HandleDropPuzzlePiece(APuzzlePieceBase* Piece, AActor* TargetActor)
{
	if (!TargetActor || !Piece)
	{
		UE_LOG(LogTemp, Warning, TEXT("Slot or PieceClass is null in %s"), *this->GetName());
		return;
	}

	APuzzlePieceSlotBase* Slot = Cast<APuzzlePieceSlotBase>(TargetActor);
	if (Slot) 
	{
		// Swap logic
		if (!Slot->GetSlotState().IsEmpty())
		{
			AssignPieceToSlot(Slot->GetSlotState().GetCurrentPiece(), Piece->CurrentSlot);
			AssignPieceToSlot(Piece, Slot);
		}
		else
		{
			AssignPieceToSlot(Piece, Slot);
		}
	}
	else
	{
		AssignPieceToSlot(Piece, Piece->CurrentSlot);
	}

	SetPuzzlePiecesCollision(true);
	Piece->bOnDrag = false;
	Piece->BP_HandleDropFromSlotEvent();
	HandleMoveMade();
}

TSubclassOf<APuzzlePieceBase> US_PuzzleManager::FindPieceClassByWidget(TSubclassOf<UW_PuzzlePieceBase> WidgetClass) const
{
	if (!WidgetClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("WidgetClass is null in %s"), *this->GetName());
		return nullptr;
	}

	for (const FPuzzleMapping& Mapping : DS_PuzzleManager->PuzzleMap)
	{
		if (!Mapping.PieceWidgetClass.IsValid())
		{
			Mapping.PieceWidgetClass.LoadSynchronous();
		}

		if (Mapping.PieceWidgetClass.Get() == WidgetClass)
		{
			return Mapping.PieceClass;
		}
	}

	return nullptr;
}

void US_PuzzleManager::AssignPieceToSlot(APuzzlePieceBase* Piece, APuzzlePieceSlotBase* TargetSlot)
{
	if (!Piece || !TargetSlot)
	{
		UE_LOG(LogTemp, Warning, TEXT("AssignPieceToSlot failed: null Piece or Slot"));
		return;
	}

	FPuzzleSlotState NewState = TargetSlot->GetSlotState();
	NewState.SetIsEmpty(false);
	NewState.SetCurrentPiece(Piece);
	NewState.SetHasCorrectPiece(IsCorrectPlacement(Piece->GetClass(), TargetSlot->GetClass()));
	TargetSlot->UpdateSlotState(NewState);

	// Piece update
	Piece->SetActorLocation(TargetSlot->GetPiecePlacementPointLocation());
	Piece->CurrentSlot = TargetSlot;
}

void US_PuzzleManager::HandleMoveMade()
{
	MoveCount++;
	OnMoveCountUpdated.Broadcast(MoveCount);

	if (IsPuzzleCompleted())
	{
		PuzzleCompleted();
	}
}

bool US_PuzzleManager::IsCorrectPlacement(TSubclassOf<APuzzlePieceBase> PieceClass, TSubclassOf<APuzzlePieceSlotBase> SlotClass)
{
	for (const FPuzzleMapping& Mapping : DS_PuzzleManager->PuzzleMap)
	{
		if (!Mapping.PieceTargetSlot) 
		{
			continue;
		}

		if (!Mapping.PieceTargetSlot.IsValid()) 
		{
			Mapping.PieceTargetSlot.LoadSynchronous();
		}

		// Comparing classes instead of instance pointers to avoid mismatches,
        // because the actual slot instances in the level and the references
        // stored in the data asset may be different objects,
        // but their classes uniquely identify the intended slot types.
		if (PieceClass == Mapping.PieceClass && SlotClass == Mapping.PieceTargetSlot->GetClass())
		{
			return true;
		}
	}

	return false;
}

bool US_PuzzleManager::IsPuzzleCompleted() const
{
	if (DS_PuzzleManager->PuzzleMap.IsEmpty()) 
	{
		UE_LOG(LogTemp, Warning, TEXT("PuzzleMap is empty in: %s!"), *GetName());
		return false;
	}

	for (const FPuzzleMapping& Mapping : DS_PuzzleManager->PuzzleMap)
	{
		if (!Mapping.PieceTargetSlot)
		{
			continue;
		}

		if (!Mapping.PieceTargetSlot.IsValid())
		{
			Mapping.PieceTargetSlot.LoadSynchronous();
		}

		if (!Mapping.PieceTargetSlot || !Mapping.PieceTargetSlot->GetSlotState().HasCorrectPiece())
		{
			return false;
		}
	}

	return true;
}

void US_PuzzleManager::PuzzleCompleted()
{
	// Broadcast game stats to listeners
	OnPuzzleCompleted.Broadcast(FGameStats(MoveCount, Time));

	// Disable player input
	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		PC->DisableInput(PC);
	}
}

void US_PuzzleManager::SetPuzzlePiecesCollision(bool bEnable)
{
	if (PuzzlePieceInstances.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("PuzzlePieceInstances is empty in: %s!"), *GetName());
		return;
	}

	for (APuzzlePieceBase* PuzzleInstance : PuzzlePieceInstances)
	{
		if (bEnable)
		{
			PuzzleInstance->SetCollisionEnabled();
		}
		else
		{
			PuzzleInstance->SetCollisionDisabled();
		}
	}
}




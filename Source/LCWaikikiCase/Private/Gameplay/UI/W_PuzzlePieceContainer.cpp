// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/UI/W_PuzzlePieceContainer.h"
#include "Gameplay/UI/W_PuzzlePieceBase.h"
#include "Gameplay/Managers/DS_UIManager.h"
#include "Components/Spacer.h"
#include "Blueprint/WidgetTree.h"

void UW_PuzzlePieceContainer::NativeConstruct()
{
	Super::NativeConstruct();

	DS_UIManager = GetDefault<UDS_UIManager>();
	if (!DS_UIManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("DS_UIManager is null in %s"), *this->GetName());
		return;
	}

	LoadPuzzlePiecesToLocal();
	ShuffleArrayManually(LocalPuzzlePieces);
	CreatePiecesAndAddToVerticalBox();
}

void UW_PuzzlePieceContainer::LoadPuzzlePiecesToLocal()
{
	for (const TSoftClassPtr<UW_PuzzlePieceBase>& SoftClass : DS_UIManager->PuzzlePieceWidgetClasses)
	{
		TSubclassOf<UW_PuzzlePieceBase> LoadedClass = SoftClass.LoadSynchronous(); // Or async if needed
		if (LoadedClass)
		{
			LocalPuzzlePieces.Add(LoadedClass);
		}
	}
}

void UW_PuzzlePieceContainer::ShuffleArrayManually(TArray<TSubclassOf<UW_PuzzlePieceBase>>& Array)
{
	for (int32 i = 0; i < Array.Num() - 1; ++i)
	{
		int32 j = FMath::RandRange(i, Array.Num() - 1);
		Array.Swap(i, j);
	}
}

void UW_PuzzlePieceContainer::CreatePiecesAndAddToVerticalBox()
{
	for (int32 i = 0; i < LocalPuzzlePieces.Num(); i++)
	{
		UW_PuzzlePieceBase* CreatedPuzzlePiece = CreatePuzzlePiece(LocalPuzzlePieces[i]);
		if (!CreatedPuzzlePiece)
		{
			UE_LOG(LogTemp, Warning, TEXT("PuzzlePieceInstance couldn't be created in %s."), *this->GetName());
			continue;
		}

		// Alternate between the three vertical boxes
		if (i % 3 == 0)
		{
			AddPuzzlePieceToVerticalBox(VB_PuzzlePieces1, CreatedPuzzlePiece);
		}
		else if(i % 3 == 1)
		{
			AddPuzzlePieceToVerticalBox(VB_PuzzlePieces2, CreatedPuzzlePiece);
		}
		else
		{
			AddPuzzlePieceToVerticalBox(VB_PuzzlePieces3, CreatedPuzzlePiece);
		}
		
	}
}

UW_PuzzlePieceBase* UW_PuzzlePieceContainer::CreatePuzzlePiece(TSubclassOf<UW_PuzzlePieceBase> PuzzlePieceClass)
{
	if (!PuzzlePieceClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("PuzzlePieceClass is null in: %s."), *this->GetName());
		return nullptr;
	}

	UW_PuzzlePieceBase* PuzzlePieceInstance = Cast<UW_PuzzlePieceBase>(CreateWidget<UW_PuzzlePieceBase>(this, PuzzlePieceClass, FName()));
	return PuzzlePieceInstance;
}

void UW_PuzzlePieceContainer::AddPuzzlePieceToVerticalBox(TObjectPtr<UVerticalBox> VerticalBox, UW_PuzzlePieceBase* PuzzlePiece)
{
	VerticalBox->AddChild(PuzzlePiece);

	// Adding a spacer to improve the UI layout
	USpacer* Spacer = WidgetTree->ConstructWidget<USpacer>(USpacer::StaticClass());
	if (Spacer)
	{
		Spacer->SetSize(FVector2D(50, 50));
		VerticalBox->AddChild(Spacer);
	}
}

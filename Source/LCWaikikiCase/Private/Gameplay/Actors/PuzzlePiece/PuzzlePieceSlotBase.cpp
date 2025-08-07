// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Actors/PuzzlePiece/PuzzlePieceSlotBase.h"

APuzzlePieceSlotBase::APuzzlePieceSlotBase()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent->SetMobility(EComponentMobility::Movable);

	PiecePlacementPoint = CreateDefaultSubobject<USceneComponent>(TEXT("PiecePlacementPoint"));
	PiecePlacementPoint->SetupAttachment(RootComponent);
	PiecePlacementPoint->SetMobility(EComponentMobility::Movable);

	SMC_PuzzlePieceSlotBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SMC_PuzzlePieceSlotBase"));
	SMC_PuzzlePieceSlotBase->SetupAttachment(RootComponent);
	SMC_PuzzlePieceSlotBase->SetMobility(EComponentMobility::Movable);
}

FVector APuzzlePieceSlotBase::GetPiecePlacementPointLocation()
{
	return PiecePlacementPoint->GetComponentLocation();
}


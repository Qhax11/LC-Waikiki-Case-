// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Actors/PuzzlePiece/PuzzlePieceBase.h"

APuzzlePieceBase::APuzzlePieceBase()
{
	PrimaryActorTick.bCanEverTick = false;

	SMC_PuzzlePiece = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SMC_PuzzlePiece"));
	SetRootComponent(SMC_PuzzlePiece);
}

void APuzzlePieceBase::SetCollisionEnabled()
{
	if (SMC_PuzzlePiece) 
	{
		SMC_PuzzlePiece->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
}

void APuzzlePieceBase::SetCollisionDisabled()
{
	if (SMC_PuzzlePiece)
	{
		SMC_PuzzlePiece->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}


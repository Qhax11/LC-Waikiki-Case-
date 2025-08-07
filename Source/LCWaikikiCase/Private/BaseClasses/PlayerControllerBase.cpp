// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClasses/PlayerControllerBase.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"

void APlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();

    if (ULocalPlayer* LP = GetLocalPlayer())
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LP))
        {
            if (DefaultMappingContext)
            {
                Subsystem->AddMappingContext(DefaultMappingContext, 0);
                UE_LOG(LogTemp, Warning, TEXT("Mapping context added successfully"));
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("DefaultMappingContext is null on %s"), *GetName());
            }
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to get EnhancedInputLocalPlayerSubsystem"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("GetLocalPlayer returned null"));
    }
}

void APlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
    {
        if (IA_LeftMouse)
        {
            EnhancedInputComponent->BindAction(IA_LeftMouse, ETriggerEvent::Started, this, &APlayerControllerBase::OnLeftMousePressed);
            EnhancedInputComponent->BindAction(IA_LeftMouse, ETriggerEvent::Completed, this, &APlayerControllerBase::OnLeftMouseReleased);
            UE_LOG(LogTemp, Warning, TEXT("Bound Left Mouse Action"));
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("IA_LeftMouse is null on %s"), *GetName());
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("InputComponent is not UEnhancedInputComponent on %s"), *GetName());
    }
}

void APlayerControllerBase::OnLeftMousePressed(const FInputActionValue& Value)
{
	BP_OnLeftMousePressed();
}

void APlayerControllerBase::OnLeftMouseReleased(const FInputActionValue& Value)
{
    BP_OnLeftMouseReleased();
}


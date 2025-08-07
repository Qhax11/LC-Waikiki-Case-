// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "PlayerControllerBase.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

/**
 * Base player controller class that handles input bindings and mouse interaction.
 */
UCLASS()
class LCWAIKIKICASE_API APlayerControllerBase : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	UFUNCTION()
	void OnLeftMousePressed(const FInputActionValue& Value);

	UFUNCTION()
	void OnLeftMouseReleased(const FInputActionValue& Value);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnLeftMousePressed();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnLeftMouseReleased();

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_LeftMouse;
};

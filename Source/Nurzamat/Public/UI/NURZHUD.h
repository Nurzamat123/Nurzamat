// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NURZHUD.generated.h"

/**
 * 
 */
UCLASS()
class NURZAMAT_API UNURZHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void SetRespawnCountdown(float RespawnTimeRemaining);
	
	//Attribute setters
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void SetMaxHealth(float MaxHelth);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void SetCurrentHealth(float CurrentHealth);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void SetHealthPersentage(float HealthPersentage);
};

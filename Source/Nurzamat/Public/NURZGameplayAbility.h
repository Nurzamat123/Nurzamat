// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Nurzamat/Nurzamat.h"
#include "NURZGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class NURZAMAT_API UNURZGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UNURZGameplayAbility();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
		ENURZAbilityInputID AbilityInputID = ENURZAbilityInputID::None;
};

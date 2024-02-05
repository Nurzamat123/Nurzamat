// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NURZGameplayAbility.h"
#include "GA_FireBase.generated.h"

/**
 * 
 */
UCLASS()
class NURZAMAT_API UGA_FireBase : public UNURZGameplayAbility
{
	GENERATED_BODY()
	
public:
	UGA_FireBase();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

};

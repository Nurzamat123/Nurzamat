// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include <GameplayEffectTypes.h>
#include "NURZPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class NURZAMAT_API ANURZPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	ANURZPlayerState();

	UAbilitySystemComponent* GetAbilitySystemComponent()const override;

	class UNURZAttributeSet* GetAttributeSet()const;

	//Getters for attributes
	UFUNCTION(BlueprintCallable, Category = "NURZPlayerState|Attributes")
		float GetHealth()const;
	UFUNCTION(BlueprintCallable, Category = "NURZPlayerState|Attributes")
		float GetMaxHealth()const;

	void HealthChanged(float AttHealth);
protected:
	UPROPERTY()
		class UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
		class UNURZAttributeSet* AttributeSet;

	FGameplayTag DeadTag;

	virtual void BeginPlay()override;


};

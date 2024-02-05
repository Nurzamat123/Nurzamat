// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NURZGameplayAbility.h"
#include "Weapon/NURZProjectile.h"
#include "GA_Fire.generated.h"

UCLASS()
class NURZAMAT_API UGA_Fire : public UNURZGameplayAbility
{
	GENERATED_BODY()

public:
	UGA_Fire();

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		UAnimMontage* FireHipMontage;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		UAnimMontage* FireADSMontage;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<ANURZProjectile>ProjectileClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		TSubclassOf<UGameplayEffect>DamageGameplayEffect;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float Range;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float Damage;

	UFUNCTION()
		void FireProjectile();
};

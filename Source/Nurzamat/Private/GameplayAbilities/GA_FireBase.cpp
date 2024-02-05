// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilities/GA_FireBase.h"
#include "AbilitySystemComponent.h"
#include "NURZCharacter.h"
#include "Weapon/WeaponComponent.h"
#include "Weapon/WeaponBase.h"
#include "Nurzamat/Nurzamat.h"

UGA_FireBase::UGA_FireBase()
{
	AbilityInputID = ENURZAbilityInputID::Fire;
}

void UGA_FireBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{

	ANURZCharacter* Character = Cast<ANURZCharacter>(GetAvatarActorFromActorInfo());

	if (Character->HasAuthority())
	{
		Character->AbilitySystemComponent->TryActivateAbilitiesByTag(FGameplayTagContainer(FGameplayTag::RequestGameplayTag(Character->GetWeaponComponent()->GetCurrentWeapon()->FireTag.GetTagName())));
	}
	

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}

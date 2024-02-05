// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayAbilities/GA_Fire.h"
#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Nurzamat/Public/NURZCharacter.h"
#include "Weapon/WeaponBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Weapon/WeaponComponent.h"

UGA_Fire::UGA_Fire()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	FGameplayTag FireTag = FGameplayTag::RequestGameplayTag(FName("Ability.Fire"));
	AbilityTags.AddTag(FireTag);
	ActivationOwnedTags.AddTag(FireTag);

	Range = 1000.0f;
	Damage = 10.0f;
}

void UGA_Fire::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	}
	//UAnimMontage* MontageToPlay = FireHipMontage;
	//if (GetAbilitySystemComponentFromActorInfo()->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("Ability.ADS"))))
	//{
	//	MontageToPlay = FireADSMontage;
	//}
	FireProjectile();

}

void UGA_Fire::FireProjectile()
{

	if (GetOwningActorFromActorInfo()->GetLocalRole() == ROLE_Authority)
	{
		ANURZCharacter* Hero = Cast<ANURZCharacter>(GetAvatarActorFromActorInfo());
		if (!Hero)
		{
			EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
		}
		if (!Hero->GetWeaponComponent()->GetCurrentWeapon()->IsClipEmpty())
		{
			FVector Start = Hero->GetWeaponMesh()->GetSocketLocation(FName("Muzzle"));
			FVector End = Hero->GetCameraBoom()->GetComponentLocation() + Hero->GetFollowCamera()->GetForwardVector() * Range;
			FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(Start, End);

			FGameplayEffectSpecHandle DamageEffectSpecHandle = MakeOutgoingGameplayEffectSpec(DamageGameplayEffect, 1);

			DamageEffectSpecHandle.Data.Get()->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Damage")), Damage);

			FTransform MuzzleTransform = Hero->GetWeaponMesh()->GetSocketTransform(FName("Muzzle"));
			MuzzleTransform.SetRotation(Rotation.Quaternion());
			MuzzleTransform.SetScale3D(FVector(1.0f));

			FActorSpawnParameters SpawnParameters;
			SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			ANURZProjectile* Projectile = GetWorld()->SpawnActorDeferred<ANURZProjectile>(ProjectileClass, MuzzleTransform, GetOwningActorFromActorInfo(),
				Hero, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
			Projectile->DamageEffectSpecHandle = DamageEffectSpecHandle;
			Projectile->Range = Range;
			Projectile->FinishSpawning(MuzzleTransform);

			Hero->GetWeaponComponent()->Decrease();
		}	
	}
	else {
		ANURZCharacter* Hero = Cast<ANURZCharacter>(GetAvatarActorFromActorInfo());
		if (Hero) {
			Hero->GetWeaponComponent()->Decrease();
		}
	}
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}



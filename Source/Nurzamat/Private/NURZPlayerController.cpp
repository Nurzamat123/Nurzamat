// Fill out your copyright notice in the Description page of Project Settings.


#include "NURZPlayerController.h"
#include "NURZGameplayAbility.h"
#include "AbilitySystemComponent.h"
#include "NURZCharacter.h"
#include "NURZPlayerState.h"
#include "Nurzamat/Nurzamat.h"

void ANURZPlayerController::DieHero()
{
	ANURZCharacter* Hero = Cast<ANURZCharacter>(GetPawn());
	Hero->Die();
}

void ANURZPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ANURZPlayerState* PS = GetPlayerState<ANURZPlayerState>();
	if (PS)
	{
		if (ANURZCharacter* NurzChar = Cast< ANURZCharacter>(InPawn)) {
			NurzChar->AbilitySystemComponent = PS->GetAbilitySystemComponent();
			NurzChar->AbilitySystemComponent->InitAbilityActorInfo(NurzChar, NurzChar);
			NurzChar->GiveAbilities();
			NurzChar->InitializeAttributes();
		}
	}
}

void ANURZPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();


}

void ANURZPlayerController::AcknowledgePossession(APawn* P)
{
	Super::AcknowledgePossession(P);
	ANURZPlayerState* PS = GetPlayerState<ANURZPlayerState>();
	if (PS)
	{
		if (ANURZCharacter* NurzChar = Cast< ANURZCharacter>(P)) {
			NurzChar->AbilitySystemComponent = PS->GetAbilitySystemComponent();
			NurzChar->AbilitySystemComponent->InitAbilityActorInfo(NurzChar, NurzChar);
			NurzChar->GiveAbilities();
			NurzChar->InitializeAttributes();
		}
	}

	
}

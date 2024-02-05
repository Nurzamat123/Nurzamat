// Fill out your copyright notice in the Description page of Project Settings.


#include "NURZPlayerState.h"
#include "NURZAttributeSet.h"
#include "Nurzamat/Public/Components/NURZAbilitySystemComponent.h"
#include "NURZCharacter.h"
#include "Nurzamat/Public/NURZPlayerController.h"
#include "UI/NURZWidgetHealth.h"
#include "UI/NURZHUD.h"

ANURZPlayerState::ANURZPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UNURZAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UNURZAttributeSet>(TEXT("AttributeSet"));

	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
}

UAbilitySystemComponent* ANURZPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UNURZAttributeSet* ANURZPlayerState::GetAttributeSet() const
{
	return AttributeSet;
}

float ANURZPlayerState::GetHealth() const
{
	return AttributeSet->GetHealth();
}

float ANURZPlayerState::GetMaxHealth() const
{
	return AttributeSet->GetMaxHealth();

}

void ANURZPlayerState::BeginPlay()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("2"));
	Super::BeginPlay();
	if (AbilitySystemComponent)
	{
			AttributeSet->OnAttHealthChangedDel.AddUObject(this, &ANURZPlayerState::HealthChanged);
	}

	//HealthChanged(GetHealth());
}

void ANURZPlayerState::HealthChanged(float AttHealth)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("VALIID"));
	ANURZPlayerController* PC = Cast<ANURZPlayerController>(GetPlayerController());
	if (PC && AttHealth <= 0.0f)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("KKKK"));
		PC->DieHero();
	}
	else if (PC) 
	{
		PC->AttHealthChDel.Broadcast(AttHealth);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Broadcast"));
	}


}




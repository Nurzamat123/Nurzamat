// Fill out your copyright notice in the Description page of Project Settings.


#include "NURZCharacter.h"
#include "Components/NURZAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "NURZAttributeSet.h"
#include "NURZGameplayAbility.h"
#include <GameplayEffectTypes.h>
#include "NURZPlayerController.h"
#include "NURZPlayerState.h"
#include "Weapon/WeaponComponent.h"

// Sets default values
ANURZCharacter::ANURZCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>("WeaponComponent");

	DeadTag = FGameplayTag::RequestGameplayTag("State.Dead");
}

void ANURZCharacter::Die()
{
	Super::Destroyed();
	WeaponComponent->DestroyComponent();

	AbilitySystemComponent->ClearAllAbilities();
}

class UAbilitySystemComponent* ANURZCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ANURZCharacter::InitializeAttributes()
{
	if (AbilitySystemComponent && DefaultAttributeEffect)
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributeEffect, 1, EffectContext);

		if (SpecHandle.IsValid())
		{
			FActiveGameplayEffectHandle GEHAndle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}
}

void ANURZCharacter::GiveAbilities()
{
	if (HasAuthority() && AbilitySystemComponent)
	{
		for (TSubclassOf<UNURZGameplayAbility>& StartupAbility : DefaultAbilities)
		{
			AbilitySystemComponent->GiveAbility(
				FGameplayAbilitySpec(StartupAbility, 1, static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID), this));
		}
	}
}



float ANURZCharacter::GetHealth() const
{
	if (AttributeSet.IsValid())
	{
		return AttributeSet->GetHealth();
	}
	return 0.0f;
}

float ANURZCharacter::GetMaxHealth()const
{
	if (AttributeSet.IsValid())
	{
		return AttributeSet->GetMaxHealth();
	}
	return 0.0f;
}

USkeletalMeshComponent* ANURZCharacter::GetWeaponMesh() const
{
	return WeaponComponent->GetWeaponMesh();
}

UWeaponComponent* ANURZCharacter::GetWeaponComponent() const
{
	return WeaponComponent;
}

void ANURZCharacter::BeginPlay()
{
	Super::BeginPlay();
}


void ANURZCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANURZCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	if (AbilitySystemComponent && InputComponent)
	{
		const FGameplayAbilityInputBinds Binds("Confirm", "Cancel", "ENURZAbilityInputID", static_cast<int32>(ENURZAbilityInputID::Confirm), static_cast<int32>(ENURZAbilityInputID::Cancel));
		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, Binds);
	}
}

bool ANURZCharacter::IsAlive() const
{
	return GetHealth()>0.0f;
}


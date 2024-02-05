#include "Weapon/WeaponBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilities/GA_Fire.h"
#include "AbilitySystemComponent.h"
#include "NURZCharacter.h"
#include "Weapon/WeaponComponent.h"

AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);
}

USkeletalMeshComponent* AWeaponBase::GetWeaponMesh() const
{
	return WeaponMesh;
}

void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	DefaultAmmo = AmmoData.Ammo;

}

void AWeaponBase::DecreaseAmmo()
{
	if (!IsClipEmpty())
	{
		AmmoData.Ammo--;
	}
	if (IsClipEmpty() && !IsAmmoEmpty())
	{
		AutoReload();
	}
}

bool AWeaponBase::IsAmmoEmpty() const
{
	return !AmmoData.Infinite&& AmmoData.Clips==0&&IsClipEmpty();
}

bool AWeaponBase::IsClipEmpty() const
{
	return AmmoData.Ammo==0;
}

void AWeaponBase::AutoReload()
{
	AmmoData.Ammo = DefaultAmmo;
	if (!AmmoData.Infinite)
	{
		AmmoData.Clips--;
	}
}






#include "Weapon/WeaponComponent.h"
#include "Weapon/WeaponBase.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/Character.h"
#include "NURZCharacter.h"

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UWeaponComponent::ChangeWeapon()
{
	ChangeWeaponMult();
}

void UWeaponComponent::ChangeWeaponMult_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("123"));
	CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	EquipWeapon(CurrentWeaponIndex);
}


USkeletalMeshComponent* UWeaponComponent::GetWeaponMesh() const
{
	return CurrentWeapon->GetWeaponMesh();
}

AWeaponBase* UWeaponComponent::GetCurrentWeapon() const
{
	return CurrentWeapon;
}


void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentWeaponIndex = 0;
	SpawnWeapons();
	EquipWeapon(CurrentWeaponIndex);

	if (ANURZCharacter* Character = Cast<ANURZCharacter>(GetOwner())) {
		
		Character->AmmoChangedDel.Broadcast(CurrentWeapon->AmmoData.Ammo, CurrentWeapon->AmmoData.Clips);
	}

}

void UWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CurrentWeapon = nullptr;
	for (auto Weapon : Weapons)
	{
		Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Weapon->Destroy();
	}
	Weapons.Empty();
	Super::EndPlay(EndPlayReason);
}

void UWeaponComponent::SpawnWeapons()
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character|| !GetWorld())return;

	for (auto WeaponClass : WeaponClasses)
	{
		auto Weapon = GetWorld()->SpawnActor<AWeaponBase>(WeaponClass);
		if (!Weapon) return;

		Weapon->SetOwner(Character);
		Weapons.Add(Weapon);
		AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
	}
	
}

void UWeaponComponent::AttachWeaponToSocket(AWeaponBase* Weapon, USceneComponent* SceneComponent, const FName& SocketName) 
{
	if (!Weapon || !SceneComponent)return;
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}

void UWeaponComponent::WeaponReload()
{
	if (CurrentWeapon->AmmoData.Clips > 0)
	{
		CurrentWeapon->AutoReload();
		ANURZCharacter* Character = Cast<ANURZCharacter>(GetOwner());
		Character->AmmoChangedDel.Broadcast(CurrentWeapon->AmmoData.Ammo, CurrentWeapon->AmmoData.Clips);
	}
}

void UWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
	ANURZCharacter* Character = Cast<ANURZCharacter>(GetOwner());
	if (!Character)return;

	if (CurrentWeapon)
	{
		AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
	}

	CurrentWeapon = Weapons[WeaponIndex];
	AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);

	Character->AmmoChangedDel.Broadcast(CurrentWeapon->AmmoData.Ammo, CurrentWeapon->AmmoData.Clips);
}

void UWeaponComponent::Decrease()
{
	CurrentWeapon->DecreaseAmmo();
	
	if (ANURZCharacter* Character = Cast<ANURZCharacter>(GetOwner())) {
		Character->AmmoChangedDel.Broadcast(CurrentWeapon->AmmoData.Ammo, CurrentWeapon->AmmoData.Clips);
	}
}


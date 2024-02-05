// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

class AWeaponBase;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NURZAMAT_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeaponComponent();

	UFUNCTION(BlueprintCallable)
		void ChangeWeapon();

	UFUNCTION(NetMulticast, unreliable)
		void ChangeWeaponMult();

	UFUNCTION(BlueprintCallable)
	void EquipWeapon(int32 WeaponIndex);

	UFUNCTION()
	void Decrease();

	//Getter for n
	USkeletalMeshComponent* GetWeaponMesh()const;

	UFUNCTION(BlueprintCallable)
	AWeaponBase* GetCurrentWeapon()const;



protected:
		
	//Set weapon socket Name
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		FName WeaponEquipSocketName="WeaponSocket";

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		FName WeaponArmorySocketName = "ArmorySocket";

	UPROPERTY(BlueprintReadWrite, Category = "Weapon")
		AWeaponBase* CurrentWeapon = nullptr;

	UPROPERTY(BlueprintReadWrite, Category = "Weapon")
		TArray<AWeaponBase*>Weapons;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		TArray<TSubclassOf<AWeaponBase>>WeaponClasses;

	UPROPERTY(BlueprintReadWrite, Category = "Weapon")
		int32 CurrentWeaponIndex = 0;

	UFUNCTION(BlueprintCallable)
		void WeaponReload();

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason)override;

private:
		void SpawnWeapons();

	void AttachWeaponToSocket(AWeaponBase* Weapon, USceneComponent* SceneComponent, const FName& SocketName);

};

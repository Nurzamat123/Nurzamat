// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include <GameplayEffectTypes.h>
#include "NURZCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UWeaponComponent;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWeapomAmmoChanged, int, AllAmmo, int, InMagazine);

UCLASS()
class NURZAMAT_API ANURZCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* FollowCamera;
public:
	ANURZCharacter();

	/// Gameplay abilities
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameplayAbilities")
		class UAbilitySystemComponent* AbilitySystemComponent;

	UFUNCTION(BlueprintCallable, Category = "NURZCharacter")
	virtual bool IsAlive()const;

	UPROPERTY()
	class UNURZAttributeSet* Attributes;

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent()const override;

	virtual void InitializeAttributes();
	virtual void GiveAbilities();

	

	//Getter for attributes from NURZAttributeSet 
	UFUNCTION(BlueprintCallable, Category = "NURZCharacter | Attributes")
		float GetHealth()const;
	UFUNCTION(BlueprintCallable, Category = "NURZCharacter | Attributes")
		float GetMaxHealth()const;

	//Getter for WeaponMesh from WeaponComponent
	USkeletalMeshComponent* GetWeaponMesh()const;

	UFUNCTION(BlueprintCallable)
	UWeaponComponent* GetWeaponComponent()const;

	UPROPERTY(BlueprintAssignable,BlueprintReadWrite, EditAnywhere)
		FWeapomAmmoChanged AmmoChangedDel;
protected:

	virtual void BeginPlay() override;

	//TWeakptr for getting attribute from PS 
	TWeakObjectPtr<class UNURZAttributeSet>AttributeSet;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
		UWeaponComponent* WeaponComponent;

	//Death animation
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Animation")
		UAnimMontage* DeathMontage;

	//Set DefaultAttributes
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Gameplay Ability")
		TSubclassOf<class UGameplayEffect>DefaultAttributeEffect;
	//Set DeafultAbilities
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Gameplay Ability")
		TArray<TSubclassOf<class UNURZGameplayAbility>>DefaultAbilities;

	
	FGameplayTag DeadTag;


public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	virtual void Die();
};

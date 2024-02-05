// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "NURZAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName) 



DECLARE_MULTICAST_DELEGATE_OneParam(FAttributeChangeDel, float);

UCLASS()
class NURZAMAT_API UNURZAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UNURZAttributeSet();
		FAttributeChangeDel OnAttHealthChangedDel;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UNURZAttributeSet, Health)

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UNURZAttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UNURZAttributeSet, Damage)

	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);
	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);

	void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue)const ;
	void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue);
	void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue);
	void ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const;
};

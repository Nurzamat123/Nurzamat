// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffect.h"
#include "NURZProjectile.generated.h"

UCLASS()
class NURZAMAT_API ANURZProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ANURZProjectile();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Meta = (ExposeOnSpawn = true))
		float Range;

	UPROPERTY(BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
		FGameplayEffectSpecHandle DamageEffectSpecHandle;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		class UProjectileMovementComponent* ProjectileMovement;

protected:
	virtual void BeginPlay() override;


};

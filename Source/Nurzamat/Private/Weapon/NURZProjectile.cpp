// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon/NURZProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

ANURZProjectile::ANURZProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovement"));
}

void ANURZProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}



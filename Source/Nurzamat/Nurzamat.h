// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ENURZAbilityInputID : uint8
{
	None,
	Confirm,
	Cancel,
	Fire,
	ADS,
	Sprint,
	Change,
	Reload,
	AutoReload
};
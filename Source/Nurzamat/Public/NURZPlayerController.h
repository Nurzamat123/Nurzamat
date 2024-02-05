// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NURZCharacter.h"
#include "NURZPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttHealthChDel, float, Health);

/**
 * 
 */
UCLASS()
class NURZAMAT_API ANURZPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
 void DieHero();

 UPROPERTY(BlueprintAssignable)
	 FAttHealthChDel AttHealthChDel;




protected:

	virtual void OnPossess(APawn* InPawn)override;
	virtual void OnRep_PlayerState()override;
	void AcknowledgePossession(APawn* P)override;
	virtual void BeginPlay()override;
};

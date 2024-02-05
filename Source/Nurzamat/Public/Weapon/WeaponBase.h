#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "WeaponBase.generated.h"

class USkeletalMeshComponent;

USTRUCT(BlueprintType)
struct FAmmoData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo",meta = (EditCondition="!Infinite"))
		int32 Clips=0;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Ammo")
		int32 Ammo=0;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Ammo")
		bool Infinite;
};

UCLASS()
class NURZAMAT_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeaponBase();

	//Getter for WeaponMesh
	USkeletalMeshComponent* GetWeaponMesh()const;

	UPROPERTY(EditAnyWhere,BlueprintReadWrite)
	FAmmoData AmmoData;
	
	float DefaultAmmo;

	UFUNCTION(BlueprintCallable)
	void DecreaseAmmo();

	UFUNCTION(BlueprintCallable)
	bool IsAmmoEmpty()const;

	UFUNCTION(BlueprintCallable)
	bool IsClipEmpty()const;
	
	void AutoReload();

	class UWeaponComponent* WeaponComp;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FGameplayTag FireTag;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		USkeletalMeshComponent* WeaponMesh;


	virtual void BeginPlay() override;
};

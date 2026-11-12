// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include <Abilities/GameplayAbility.h>
#include "AbilityInfoDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FAbilityInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability Info")
	FGameplayTag AbilityTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability Info")
	TSoftObjectPtr<UTexture2D> Icon = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability Info")
	TSoftObjectPtr<UMaterialInterface> BackgroundMaterial = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability Info")
	TSubclassOf<UGameplayAbility> AbilityClass = nullptr;
};

UCLASS()
class JUSTASWORD_API UAbilityInfoDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability Info")
	TArray<FAbilityInfo> AbilityInformation;
	
	UFUNCTION(BlueprintCallable, Category = "Ability Info")
	FAbilityInfo FindAbilityInfo(const UGameplayAbility* TargetAbility, bool& bFound, bool bLogNotFound = false) const
	{
		bFound = false;

		// Pre-check target ability vailidty
		if (!IsValid(TargetAbility))
		{
			if (bLogNotFound)
			{
				UE_LOG(LogTemp, Warning, TEXT("Target Ability Class is Empty"));
			}
			return FAbilityInfo();
		}
		
		// Get abilty info data
		for (const FAbilityInfo& Info : AbilityInformation)
		{

			if (Info.AbilityClass && TargetAbility->IsA(Info.AbilityClass))
			{
				bFound = true;
				return Info;
			}
		}

		if (bLogNotFound)
		{
			UE_LOG(LogTemp, Warning, TEXT("Can't find info for Ability Info for Ability : [%s]"), *GetNameSafe(TargetAbility->GetClass()));
		}

		return FAbilityInfo();
	}
};

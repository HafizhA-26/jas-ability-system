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
	FAbilityInfo FindAbilityInfo(const UGameplayAbility* TargetAbility, bool& bFound, bool bLogNotFound = false) const;
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "JustASword/GAS/AbilityInfo/AbilityInfoDataAsset.h"

FAbilityInfo UAbilityInfoDataAsset::FindAbilityInfo(const UGameplayAbility* TargetAbility, bool& bFound, bool bLogNotFound) const
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
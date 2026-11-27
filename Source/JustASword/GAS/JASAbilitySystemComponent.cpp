// Fill out your copyright notice in the Description page of Project Settings.


#include "JASAbilitySystemComponent.h"
#include "Characters/JASCharacterBase.h"

void UJASAbilitySystemComponent::OnRep_ActivateAbilities()
{
	Super::OnRep_ActivateAbilities();

	AJASCharacterBase* Character = Cast<AJASCharacterBase>(GetOwner());

	if (!Character) return;

	bool bAbilityChanged = false;
	if (LastActivatableAbilities.Num() != ActivatableAbilities.Items.Num())
	{
		bAbilityChanged = true;
	}
	else 
	{
		for (int32 i = 0; i < LastActivatableAbilities.Num(); i++)
		{
			if (LastActivatableAbilities[i].Ability != ActivatableAbilities.Items[i].Ability)
			{
				bAbilityChanged = true;
				break;
			}
		}
	}

	if (bAbilityChanged)
	{
		Character->SendAbilitiesChangedEvent();
		LastActivatableAbilities = ActivatableAbilities.Items;
	}
}

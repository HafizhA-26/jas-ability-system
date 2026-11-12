// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "BaseAttributes.generated.h"

/**
 * 
 */
UCLASS()
class JUSTASWORD_API UBaseAttributes : public UAttributeSet
{
	GENERATED_BODY()
	
public :

	UBaseAttributes();

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS_BASIC(UBaseAttributes, Health);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS_BASIC(UBaseAttributes, MaxHealth);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Energy)
	FGameplayAttributeData Energy;
	ATTRIBUTE_ACCESSORS_BASIC(UBaseAttributes, Energy);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_MaxEnergy)
	FGameplayAttributeData MaxEnergy;
	ATTRIBUTE_ACCESSORS_BASIC(UBaseAttributes, MaxEnergy);

public: 

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData OldValue) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributes, Health, OldValue)
	}

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData OldValue) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributes, MaxHealth, OldValue)
	}

	UFUNCTION()
	void OnRep_Energy(const FGameplayAttributeData OldValue) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributes, Energy, OldValue)
	}

	UFUNCTION()
	void OnRep_MaxEnergy(const FGameplayAttributeData OldValue) const
	{
		GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributes, MaxEnergy, OldValue)
	}

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
};

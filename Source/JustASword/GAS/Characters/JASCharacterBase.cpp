// Fill out your copyright notice in the Description page of Project Settings.


#include "JASCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include <AbilitySystemBlueprintLibrary.h>
#include <JustASword/GAS/JASAbilitySystemComponent.h>
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AJASCharacterBase::AJASCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UJASAbilitySystemComponent>(TEXT("AbilitySystem"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(ASCReplicationMode);

	GetCapsuleComponent()->InitCapsuleSize(35.0f, 90.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
	MovementComponent->bOrientRotationToMovement = true;
	MovementComponent->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	MovementComponent->JumpZVelocity = 500.0f;
	MovementComponent->AirControl = 0.35f;
	MovementComponent->MaxWalkSpeed = 500.0f;
	MovementComponent->MinAnalogWalkSpeed = 20.0f;
	MovementComponent->BrakingDecelerationWalking = 2000.0f;
	MovementComponent->BrakingDecelerationFalling = 1500.0f;

	// Add basic attributes
	BasicAttributes = CreateDefaultSubobject<UBaseAttributes>(TEXT("BasicAttributes"));
}

// Called when the game starts or when spawned
void AJASCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJASCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AJASCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AJASCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		GrantAbilities(StartAbilities);
	}
}

void AJASCharacterBase::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

UAbilitySystemComponent* AJASCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

TArray<FGameplayAbilitySpecHandle> AJASCharacterBase::GrantAbilities(TArray<TSubclassOf<UGameplayAbility>> AbilitiesToGrant)
{
	if (!AbilitySystemComponent || !HasAuthority())
	{
		return TArray<FGameplayAbilitySpecHandle>();
	}

	TArray<FGameplayAbilitySpecHandle> SpecHandles;

	for (TSubclassOf<UGameplayAbility> Ability : AbilitiesToGrant)
	{
		FGameplayAbilitySpecHandle SpecHandle = AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability, 1, -1, this));
		SpecHandles.Add(SpecHandle);
	}
	
	SendAbilitiesChangedEvent();

	return SpecHandles;
}

void AJASCharacterBase::ClearAbilities(TArray<FGameplayAbilitySpecHandle> AbilityHandlesToRemove)
{
	if (!AbilitySystemComponent || !HasAuthority())
	{
		return;
	}

	for (FGameplayAbilitySpecHandle SpecHandle : AbilityHandlesToRemove)
	{
		AbilitySystemComponent->ClearAbility(SpecHandle);
	}

	SendAbilitiesChangedEvent();
}

void AJASCharacterBase::SendAbilitiesChangedEvent()
{
	FGameplayEventData EventData;
	EventData.EventTag = FGameplayTag::RequestGameplayTag(FName("GameplayAbility.SkillsEvent.Changed"));
	EventData.Instigator = this;
	EventData.Target = this;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, EventData.EventTag, EventData);


}

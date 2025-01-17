// Fill out your copyright notice in the Description page of Project Settings.
#include "SHealthComponent.h"
#include "Net/UnrealNetwork.h"
#include "SCharacter.h"
#include "GameFramework/Controller.h"

// Sets default values for this component's properties
USHealthComponent::USHealthComponent()
{
	MaxHealth = 100;
	SetIsReplicated(true);
}

// Called when the game starts
void USHealthComponent::BeginPlay()
{
	Super::BeginPlay();


	AActor* MyOwner = GetOwner();
	if (MyOwner && MyOwner->Role == ROLE_Authority)
	{
		MyOwner->OnTakeAnyDamage.AddDynamic(this, &USHealthComponent::HandleTakeAnyDamage);
	}
	

	Health = MaxHealth;
}

void USHealthComponent::HandleTakeAnyDamage(AActor * DamagedActor, float Damage, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser)
{
	if (Damage <= 0.0f) 
	{
		return;
	}

	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);

	UE_LOG(LogTemp, Log, TEXT("Health Changed: %s"), *FString::SanitizeFloat(Health));

	OnHealthChanged.Broadcast(this, Health, Damage, DamageType, InstigatedBy, DamageCauser);


	if (InstigatedBy) 
	{
		ASCharacter* Character = Cast<ASCharacter>(InstigatedBy->GetPawn());

		if (Character)
		{
			Character->NotifyDamageDealt(Damage);
		}
	}
}

bool USHealthComponent::IsAlive()
{
	return Health > 0;
}

void USHealthComponent::ForceHealthTo(float amount)
{
	HandleTakeAnyDamage(nullptr, Health, nullptr, nullptr, nullptr);
}

void USHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USHealthComponent, Health);
}
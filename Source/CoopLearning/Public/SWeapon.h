// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SWeapon.generated.h"

class USkeletalMeshComponent;
class UDamageType;
class UParticleSystem;
class UCameraShake;

USTRUCT()
struct FMulticastShotData 
{
	GENERATED_BODY();

public:

	UPROPERTY()
	bool HitTarget;

	UPROPERTY()
	FVector_NetQuantize TraceEndPoint;

	UPROPERTY()
	FVector_NetQuantize ImpactPoint;

	UPROPERTY()
	FVector_NetQuantizeNormal ImpactNormal;

	UPROPERTY()
	TEnumAsByte<EPhysicalSurface> SurfaceType;

};

UCLASS()
class COOPLEARNING_API ASWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASWeapon();


protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* MeshComp;

	void PlayFireEffects(FVector TracerEndPoint);

	void PlayImpactEffects(FVector ImpactPoint, FVector ImpactNormal, EPhysicalSurface SurfaceType);

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float BaseDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FName MuzzleSocketName;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FName TracerTargetName;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	UParticleSystem* MuzzleEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	UParticleSystem* DefaultImpactEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	UParticleSystem* FleshImpactEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	UParticleSystem* TracerEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<UCameraShake> FireCamShake;

	virtual void Fire();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerFire();

	UFUNCTION(NetMulticast, Reliable)
	void MultiCastFire(FMulticastShotData MulticastData);

	FTimerHandle TimerHandle_TimeBetweenShots;

	float LastFireTimeStamp;

	//ShotsPerMin
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float RateOfFire;

	float TimeBetweenShots;

public:
	void StartFire();

	void StopFire();

};
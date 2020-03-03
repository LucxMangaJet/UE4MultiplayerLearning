// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CoopLearningPlayerController.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPossessSignature, class ACoopLearningPlayerController*, PC,  APawn*, NewPawn);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUnPossessSignature, class ACoopLearningPlayerController*, PC);



UCLASS()
class COOPLEARNING_API ACoopLearningPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	
	UFUNCTION(BlueprintCallable)
	void RespawnDefaultPawnAndPossess();

	void OnPossess(APawn* InPawn) override;

	void OnUnPossess() override;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnPossessSignature OnPossessWithAuthority;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnUnPossessSignature OnUnPossessWithAuthority;
};

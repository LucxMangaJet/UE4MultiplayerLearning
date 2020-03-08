// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "CoopLearningPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class COOPLEARNING_API ACoopLearningPlayerState : public APlayerState
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(Replicated, BlueprintReadOnly)
	int Kills;

	UPROPERTY(Replicated, BlueprintReadOnly)
	int Deaths;

	UPROPERTY(Replicated, BlueprintReadOnly)
	FLinearColor Color;

public:
	UFUNCTION(BlueprintCallable)
	void AddKill();

	UFUNCTION(BlueprintCallable)
	void AddDeath();

	int GetKills();

	int GetDeaths();

	void Reset();

	UFUNCTION(BlueprintCallable)
	FString GetPlayerInfo();

	UFUNCTION(BlueprintCallable)
	void SetName(FString S);

	UFUNCTION(BlueprintCallable)
	void SetColor(FLinearColor NewColor);
};

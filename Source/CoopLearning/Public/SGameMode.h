// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "SGameMode.generated.h"


class ASCharacter;
class ASPlayerController;
class APlayerState;

UCLASS()
class COOPLEARNING_API ASGameMode : public AGameMode
{
	GENERATED_BODY()
	
protected:

	UFUNCTION(Exec, Category = "Cheats")
		void ResetAllKDA();

	UFUNCTION()
	virtual void OnPlayerPossesWithAuthority(ASPlayerController* PC, APawn* NewPawn);
	
	UFUNCTION()
	virtual void OnPlayerCharacterDeath( ASCharacter* Character, AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION(BlueprintCallable, Category = "GameMode")
	virtual void CheckForGameEnd();

	UFUNCTION(Exec, Category = "Cheats")
	virtual void RestartGameMode();

public:

	virtual void PostLogin(APlayerController* NewPlayer) override;

	AActor* ChoseBestRespawnPlayerStart(AController* Player);

	UFUNCTION(BlueprintCallable, Category = "GameMode")
	void SetPlayerName(FString NewName, APlayerState* PlayerState);

	UFUNCTION(BlueprintCallable, Category = "GameMode")
	void SetPlayerColor(FLinearColor NewColor, APlayerState* PlayerState);
};

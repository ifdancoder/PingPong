// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PingPongPlayerState.generated.h"

/**
 * 
 */



UCLASS()
class PINGPONG_API APingPongPlayerState : public APlayerState
{
	GENERATED_BODY()

protected:
	UPROPERTY(Replicated)
	int ScoreValue = 0;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const;

public:
	
	UFUNCTION()
	void IncrementScore(int InStrengtValue);

	UFUNCTION()
	void ScoreNull();

	UFUNCTION()
	int GetScore();
};

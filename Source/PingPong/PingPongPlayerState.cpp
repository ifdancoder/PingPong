// Fill out your copyright notice in the Description page of Project Settings.


#include "PingPongPlayerState.h"
#include <Net/UnrealNetwork.h>

void APingPongPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APingPongPlayerState, ScoreValue);
}

void APingPongPlayerState::IncrementScore(int InStrengtValue)
{
	ScoreValue += InStrengtValue;
}

int APingPongPlayerState::GetScore()
{
	return ScoreValue;
}


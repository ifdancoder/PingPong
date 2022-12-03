// Fill out your copyright notice in the Description page of Project Settings.


#include "PingPongPlayerState.h"
#include <Net/UnrealNetwork.h>

void APingPongPlayerState::GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APingPongPlayerState, ScoreValue);
}

void APingPongPlayerState::IncrementScore()
{
	ScoreValue++;
}

int APingPongPlayerState::GetScore()
{
	return ScoreValue;
}

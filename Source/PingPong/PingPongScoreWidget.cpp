// Fill out your copyright notice in the Description page of Project Settings.


#include "PingPongScoreWidget.h"
#include <Components/TextBlock.h>

void UPingPongScoreWidget::ChangeYourScore(int InScore)
{
	YourScore->SetText(FText::FromString(FString::FromInt(InScore)));
}

void UPingPongScoreWidget::ChangeOpponentScore(int InScore)
{
	OpponentScore->SetText(FText::FromString(FString::FromInt(InScore)));
}

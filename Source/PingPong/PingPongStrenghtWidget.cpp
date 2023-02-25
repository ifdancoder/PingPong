// Fill out your copyright notice in the Description page of Project Settings.


#include "PingPongStrenghtWidget.h"
#include <Components/TextBlock.h>

void UPingPongStrenghtWidget::SetStrenghtValue(int InStrenghtValue)
{
	StrenghtValue->SetText(FText::FromString(FString::FromInt(InStrenghtValue)));
}

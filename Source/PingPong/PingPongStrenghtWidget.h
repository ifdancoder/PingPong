// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PingPongStrenghtWidget.generated.h"

/**
 * 
 */
UCLASS()
class PINGPONG_API UPingPongStrenghtWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
	class UTextBlock* StrenghtValue;

public:
	void SetStrenghtValue(int InStrenghtValue);
};

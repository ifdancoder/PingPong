// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PingPongScoreWidget.generated.h"

/**
 * 
 */
UCLASS()
class PINGPONG_API UPingPongScoreWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
	class UTextBlock* YourScore;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
	class UTextBlock* OpponentScore;

public:
	UFUNCTION()
	void ChangeYourScore(int InScore);

	UFUNCTION()
	void ChangeOpponentScore(int InScore);
};

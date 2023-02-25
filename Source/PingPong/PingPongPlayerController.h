// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PingPongPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PINGPONG_API APingPongPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	FTransform StartTransform;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class APingPongPlatform> PlatformClass;

	UPROPERTY()
	class APingPongPlatform* Platform;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> ScoreWidgetClass;

	UPROPERTY()
	class UUserWidget* ScoreWidget;

public:
	APingPongPlayerController();

	UFUNCTION()
	void SetStartTransfrorm(FTransform NewStartTransform);

	UFUNCTION(Server, Reliable, WithValidation)
	void Initialize();

	UFUNCTION(Server, Reliable, WithValidation)
	void SpawnPlatform(TSubclassOf<class APingPongPlatform> PlatfromClass);

	virtual void SetupInputComponent() override;

	UFUNCTION()
	void ScoreIncrement(int InStrengtValue);

	void CreateScoreWidget();

	UFUNCTION(Client, Reliable, WithValidation)
	void Client_UpdateScoreWidget();

	virtual void BeginPlay() override;

protected:
	UFUNCTION()
	void MoveRight(float AxisValue);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_PlatformMoveRight(float AxisValue);
};
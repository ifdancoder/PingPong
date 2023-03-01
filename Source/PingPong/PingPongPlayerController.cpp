// Fill out your copyright notice in the Description page of Project Settings.


#include "PingPongPlayerController.h"
#include "PingPongPlatform.h"
#include "PingPongPlayerState.h"
#include "PingPongPlayerPawn.h"
#include <Kismet/GameplayStatics.h>
#include "PingPongPlayerState.h"
#include "GameFramework/GameStateBase.h"
#include "PingPongScoreWidget.h"
#include <Net/UnrealNetwork.h>
#include <GameFramework/Actor.h>

APingPongPlayerController::APingPongPlayerController()
{
	SetReplicates(true);
}

void APingPongPlayerController::SetStartTransfrorm(FTransform
	NewStartTransform)
{
	StartTransform = NewStartTransform;
}

void APingPongPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis("Move", this,	&APingPongPlayerController::MoveRight);
}

void APingPongPlayerController::ScoreIncrement(int InStrengtValue)
{
	GetPlayerState<APingPongPlayerState>()->IncrementScore(InStrengtValue);
}

void APingPongPlayerController::ScoreNull()
{
	GetPlayerState<APingPongPlayerState>()->ScoreNull();
}

void APingPongPlayerController::HideWaitingWidget()
{
	Client_HideWaitingWidget();
}

void APingPongPlayerController::BeginPlay()
{
	if (IsLocalPlayerController() && ScoreWidgetClass)
	{
		ScoreWidget = CreateWidget(this, ScoreWidgetClass);
		ScoreWidget->AddToViewport();

		WaitingWidget = CreateWidget(this, WaitingWidgetClass);
		WaitingWidget->AddToViewport();
	}
}

void APingPongPlayerController::MoveRight(float AxisValue)
{
	if (AxisValue != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("APingPongPlayerController::MoveRight"));
	}
	Server_PlatformMoveRight(AxisValue);
}

bool APingPongPlayerController::Server_PlatformMoveRight_Validate(float AxisValue)
{
	return true;
}

void APingPongPlayerController::Server_PlatformMoveRight_Implementation(float AxisValue)
{
	if (Platform)
	{
		if (AxisValue != 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("APingPongPlayerController::Server_PlatformMoveRight_Implementation"));
		}
		Platform->Server_MoveRight(AxisValue);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("APingPongPlayerController::Server_PlatformMoveRight_Implementation: HAS NO PLATFORM!"));
	}
}

bool APingPongPlayerController::Initialize_Validate()
{
	return true;
}

void APingPongPlayerController::Initialize_Implementation()
{
	if (Platform)
		Platform->Destroy();
	SpawnPlatform(PlatformClass);
}

bool APingPongPlayerController::SpawnPlatform_Validate(TSubclassOf<class APingPongPlatform> PlatfromClass)
{
	return PlatfromClass != NULL;
}

void APingPongPlayerController::SpawnPlatform_Implementation(TSubclassOf<class APingPongPlatform> PlatfromClass)
{
	Platform = (APingPongPlatform*)GetWorld()->SpawnActor<APingPongPlatform>(PlatfromClass);
	if (Platform)
	{
		Platform->SetActorLocation(StartTransform.GetLocation());
		Platform->SetActorRotation(StartTransform.GetRotation());
	}
}

void APingPongPlayerController::Client_UpdateScoreWidget_Implementation()
{
	if (ScoreWidget)
	{
		for (APlayerState* CurrPlayerState : UGameplayStatics::GetGameState(GetWorld())->PlayerArray)
		{
			APingPongPlayerState* CurrPingPongPlayerState = Cast<APingPongPlayerState>(CurrPlayerState);
			if (CurrPlayerState->GetPawn()->GetController() == this)
			{
				Cast<UPingPongScoreWidget>(ScoreWidget)->ChangeYourScore(CurrPingPongPlayerState->GetScore());
			}
			else
			{
				Cast<UPingPongScoreWidget>(ScoreWidget)->ChangeOpponentScore(CurrPingPongPlayerState->GetScore());
			}
		}
	}
}

bool APingPongPlayerController::Client_UpdateScoreWidget_Validate()
{
	return true;
}

void APingPongPlayerController::Client_ShowWaitingWidget_Implementation()
{
	if (IsLocalPlayerController() && WaitingWidget)
	{
		WaitingWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

bool APingPongPlayerController::Client_ShowWaitingWidget_Validate()
{
	return true;
}

void APingPongPlayerController::Client_HideWaitingWidget_Implementation()
{
	if (IsLocalPlayerController() && WaitingWidget)
	{
		WaitingWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

bool APingPongPlayerController::Client_HideWaitingWidget_Validate()
{
	return true;
}

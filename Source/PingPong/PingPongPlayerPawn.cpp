// Fill out your copyright notice in the Description page of Project Settings.


#include "PingPongPlayerPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PingPongScoreWidget.h"
#include <Net/UnrealNetwork.h>
#include "PingPongGameModeBase.h"
#include "GameFramework/GameStateBase.h"
#include "PingPongPlayerController.h"
#include <Kismet/GameplayStatics.h>
#include "PingPongPlayerState.h"

APingPongPlayerPawn::APingPongPlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	USceneComponent* root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = root;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	SetReplicates(true);
}
// Called when the game starts or when spawned
void APingPongPlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocallyControlled())
	{
		if (ScoreWidgetClass)
		{
			ScoreWidget = CreateWidget(Cast<APingPongPlayerController>(GetController()), ScoreWidgetClass);
			ScoreWidget->AddToViewport();
		}
	}
}
// Called every frame
void APingPongPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
// Called to bind functionality to input
void APingPongPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APingPongPlayerPawn::Server_UpdateScoreWidget_Implementation()
{
	Multicast_UpdateScoreWidget();
}

bool APingPongPlayerPawn::Server_UpdateScoreWidget_Validate()
{
	return true;
}

void APingPongPlayerPawn::Multicast_UpdateScoreWidget_Implementation()
{
	if (ScoreWidget)
	{
		for (APlayerState* CurrPlayerState : UGameplayStatics::GetGameState(GetWorld())->PlayerArray)
		{
			APingPongPlayerState* CurrPingPongPlayerState = Cast<APingPongPlayerState>(CurrPlayerState);
			if (CurrPingPongPlayerState == GetPlayerState())
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

bool APingPongPlayerPawn::Multicast_UpdateScoreWidget_Validate()
{
	return true;
}

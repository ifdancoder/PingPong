// Copyright Epic Games, Inc. All Rights Reserved.


#include "PingPongGameModeBase.h"

#include "PingPongPlayerController.h"
#include "PingPongPlayerPawn.h"
#include "Kismet/GameplayStatics.h"
#include "PingPongBall.h"

APingPongGameModeBase::APingPongGameModeBase()
{
	DefaultPawnClass = APingPongPlayerPawn::StaticClass();
	PlayerControllerClass = APingPongPlayerController::StaticClass();
}

void APingPongGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void APingPongGameModeBase::StartGame()
{
	Ball = GetWorld()->SpawnActor<APingPongBall>(BallClass, FTransform(FRotator(0, 0, 0), BallSpawnLocation, FVector(1, 1, 1)));
	Player1->HideWaitingWidget();
	Player2->HideWaitingWidget();
}

void APingPongGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	UWorld* world = GetWorld();
	if (world && (!Player1Start || !Player2Start))
	{
		TArray<AActor*> foundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), foundActors);
		if (foundActors.Num() > 0)
			Player1Start = (APlayerStart*)foundActors[0];
		if (foundActors.Num() > 1)
			Player2Start = (APlayerStart*)foundActors[1];
	}
	APingPongPlayerController* currPlayer = NULL;
	APlayerStart* startPos = NULL;
	if (Player1 == NULL)
	{
		Player1 = (APingPongPlayerController*)NewPlayer;
		currPlayer = Player1;
		startPos = Player1Start;
		UE_LOG(LogTemp, Warning, TEXT("PingPongGameMode: Init player 1"));
	}
	else if (Player2 == NULL)
	{
		Player2 = (APingPongPlayerController*)NewPlayer;
		currPlayer = Player2;
		startPos = Player2Start;
		UE_LOG(LogTemp, Warning, TEXT("PingPongGameMode: Init player 2"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("PingPongGameMode: There are already two players in the game.New connections are not possible"));
		return;
	}
	APingPongPlayerPawn* newPawn = Cast<APingPongPlayerPawn>(NewPlayer->GetPawn());
	if (!newPawn)
	{
		newPawn = world->SpawnActor<APingPongPlayerPawn>(DefaultPawnClass);
	}
	if (startPos && newPawn)
	{
		newPawn->SetActorLocation(startPos->GetActorLocation());
		newPawn->SetActorRotation(startPos->GetActorRotation());
		NewPlayer->SetPawn(newPawn);
		currPlayer->SetStartTransfrorm(startPos->GetActorTransform());
		currPlayer->Initialize();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Start position not setted in PingPongGameMode!"));
	}
	if (Player1 && Player2)
	{
		TArray<AActor*> FoundGates = TArray<AActor*>();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APingPongGates::StaticClass(), FoundGates);
		APingPongGates* Gates1 = (APingPongGates*)FoundGates[0];
		APingPongGates* Gates2 = (APingPongGates*)FoundGates[1];
		FVector Gates1Location = Gates1->GetActorLocation();
		FVector Gates2Location = Gates2->GetActorLocation();
		FVector Player1StartLocation = Player1Start->GetActorLocation();
		FVector Player2StartLocation = Player2Start->GetActorLocation();
		if (FVector::Dist(Gates1Location, Player1StartLocation) > FVector::Dist(Gates2Location, Player1StartLocation))
		{
			Gates1->SetControllers(Player1, Player2);
			Gates2->SetControllers(Player2, Player1);
		}
		else
		{
			Gates2->SetControllers(Player1, Player2);
			Gates1->SetControllers(Player2, Player1);
		}

		FTimerHandle UnusedHandle;
		GetWorldTimerManager().SetTimer(
			UnusedHandle, this, &ThisClass::StartGame, DelayValue, false);
	}
}
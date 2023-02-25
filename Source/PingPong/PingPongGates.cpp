// Fill out your copyright notice in the Description page of Project Settings.


#include "PingPongGates.h"
#include "Components/BoxComponent.h"
#include "PingPongPlayerController.h"
#include "PingPongPlayerPawn.h"
#include "PingPongPlayerState.h"
#include <Kismet/KismetSystemLibrary.h>

// Sets default values
APingPongGates::APingPongGates()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BodyCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Gates Body Collider"));
	SetRootComponent(BodyCollision);
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gates Body Mesh"));
	BodyMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APingPongGates::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APingPongGates::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APingPongGates::HittedByBall(int InStrenghtValue)
{
	if(OwningController)
	{
		OwningController->ScoreIncrement(InStrenghtValue);
		FTimerHandle UnusedHandle;
		GetWorldTimerManager().SetTimer(
			UnusedHandle, this, &ThisClass::UpdateWidgets, DelayValue, false);
	}
}

void APingPongGates::UpdateWidgets()
{
	OwningController->Client_UpdateScoreWidget();
	if (OpponentController)
	{
		OpponentController->Client_UpdateScoreWidget();
	}
}

void APingPongGates::SetControllers(class APingPongPlayerController* InOwningController, class APingPongPlayerController* InOponentController)
{
	Server_SetControllers(InOwningController, InOponentController);
}

void APingPongGates::Server_SetControllers_Implementation(class APingPongPlayerController* InOwningController, class APingPongPlayerController* InOponentController)
{
	OwningController = InOwningController;
	OpponentController = InOponentController;
}

bool APingPongGates::Server_SetControllers_Validate(class APingPongPlayerController* InOwningController, class APingPongPlayerController* InOponentController)
{
	return true;
}

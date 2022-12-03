// Fill out your copyright notice in the Description page of Project Settings.


#include "PingPongGates.h"
#include "Components/BoxComponent.h"
#include "PingPongPlayerController.h"
#include "PingPongPlayerPawn.h"

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

void APingPongGates::HittedByBall()
{
	if(OwningController)
	{
		OwningController->ScoreIncrement();
	}
}

void APingPongGates::SetOwningController(class APingPongPlayerController* InOwningController)
{
	Server_SetOwningController(InOwningController);
}

void APingPongGates::Server_SetOwningController_Implementation(class APingPongPlayerController* InOwningController)
{
	OwningController = InOwningController;
}

bool APingPongGates::Server_SetOwningController_Validate(class APingPongPlayerController* InOwningController)
{
	return true;
}

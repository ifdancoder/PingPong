// Fill out your copyright notice in the Description page of Project Settings.


#include "PingPongGates.h"

// Sets default values
APingPongGates::APingPongGates()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BodyCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Gates Body Collider"));
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


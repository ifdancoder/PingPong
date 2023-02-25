// Fill out your copyright notice in the Description page of Project Settings.


#include "PingPongBall.h"
#include <Components/SphereComponent.h>
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"
#include "PingPongGates.h"
#include "PingPongStrenghtWidget.h"
#include <Components/WidgetComponent.h>

// Sets default values
APingPongBall::APingPongBall()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BodyCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Ball Body Collider"));
	SetRootComponent(BodyCollision);
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball Body Mesh"));
	BodyMesh->SetupAttachment(RootComponent);
	StrenghtWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Strenght Widget"));
	StrenghtWidget->SetupAttachment(RootComponent);
	BodyMesh->SetIsReplicated(true);
	SetReplicates(true);
	SetReplicateMovement(true);
}
// Called when the game starts or when spawned
void APingPongBall::BeginPlay()
{
	Super::BeginPlay();

	DefaultBallLocation = GetActorLocation();
}
// Called every frame
void APingPongBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetNetMode() != ENetMode::NM_Client)
	{
		Server_Move(DeltaTime);
	}
}
void APingPongBall::StartMove()
{
	Server_StartMove();
}
void APingPongBall::StopMove()
{
	Server_StopMove();
}
void APingPongBall::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APingPongBall, IsMoving);
}
bool APingPongBall::Server_Move_Validate(float DeltaTime)
{
	return IsMoving;
}
void APingPongBall::Server_Move_Implementation(float DeltaTime)
{
	FVector forward = GetActorForwardVector();
	FVector currLoc = GetActorLocation();
	FVector newLoc = currLoc + forward * MoveSpeed * DeltaTime;
	FHitResult hitResult;
	if (!SetActorLocation(newLoc, true, &hitResult))
	{
		if (APingPongGates* HittedGates = Cast<APingPongGates>(hitResult.Actor))
		{
			HittedGates->HittedByBall(StrenghtValue);
			StrenghtValue = 1;
			Multicast_SetStrenghtValueInWidget(StrenghtValue);
			SetActorLocation(DefaultBallLocation);
			Server_StopMove();
			FTimerHandle UnusedHandle;
			GetWorldTimerManager().SetTimer(
				UnusedHandle, this, &ThisClass::Server_StartMove, DelayValue, false);
		}
		else
		{
			FVector newForward = forward + 2 * hitResult.ImpactNormal;
			newForward.Normalize();
			float RotationOffset = UKismetMathLibrary::RandomInteger(ReboundSpread) + UKismetMathLibrary::RandomFloat();
			float RotationAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(forward, newForward))) + RotationOffset;
			FRotator newRotation = GetActorRotation();
			newRotation.Yaw = newRotation.Yaw + RotationAngle;
			SetActorLocation(currLoc);
			SetActorRotation(newRotation);
			Multicast_SetStrenghtValueInWidget(++StrenghtValue);
			Multicast_HitEffect();
		}
	}
}

bool APingPongBall::Server_StartMove_Validate()
{
	return true;
}

void APingPongBall::Server_StartMove_Implementation()
{
	IsMoving = true;
}

bool APingPongBall::Server_StopMove_Validate()
{
	return true;
}

void APingPongBall::Server_StopMove_Implementation()
{
	IsMoving = false;
}

void APingPongBall::Multicast_SetStrenghtValueInWidget_Implementation(int InStrenghtValue)
{
	if (StrenghtWidget)
	{
		if (UPingPongStrenghtWidget* OurWidget = Cast<UPingPongStrenghtWidget>(StrenghtWidget->GetUserWidgetObject()))
		{
			OurWidget->SetStrenghtValue(InStrenghtValue);
		}
	}
}

void APingPongBall::Multicast_HitEffect_Implementation()
{
	UWorld* world = GetWorld();
	if (world && HitEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, GetActorLocation());
	}
}
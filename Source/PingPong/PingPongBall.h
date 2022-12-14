// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PingPongBall.generated.h"

UCLASS()
class PINGPONG_API APingPongBall : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class USphereComponent* BodyCollision;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* BodyMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ball params")
	float MoveSpeed = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ball params")
	UParticleSystem* HitEffect;

	FVector DefaultBallLocation;

	UPROPERTY(Replicated)
	bool IsMoving = true;
public:
	// Sets default values for this actor's properties
	APingPongBall();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_Move(float DeltaTime);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_StartMove();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_StopMove();

	UFUNCTION(NetMulticast, Unreliable)
	void Multicast_HitEffect();
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void StartMove();

	UFUNCTION(BlueprintCallable)
	void StopMove();

	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps) const;
};

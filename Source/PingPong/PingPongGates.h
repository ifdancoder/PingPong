// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PingPongGates.generated.h"

UCLASS()
class PINGPONG_API APingPongGates : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APingPongGates();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UBoxComponent* BodyCollision;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* BodyMesh;

	UPROPERTY()
	class APingPongPlayerController* OwningController;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void HittedByBall();

	UFUNCTION(BlueprintCallable)
	void SetOwningController(class APingPongPlayerController* InOwningController);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_SetOwningController(class APingPongPlayerController* InOwningController);
};

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Delay")
	float DelayValue = 1;

	UPROPERTY()
	class APingPongPlayerController* OwningController;

	UPROPERTY()
	class APingPongPlayerController* OpponentController;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void HittedByBall(int InStrengtValue);

	UFUNCTION()
	void UpdateWidgets();

	UFUNCTION(BlueprintCallable)
	void SetControllers(class APingPongPlayerController* InOwningController, class APingPongPlayerController* InOponentController);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_SetControllers(class APingPongPlayerController* InOwningController, class APingPongPlayerController* InOponentController);
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "CoreMinimal.h"
#include "TankAIController.generated.h"

class ATank;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;
	ATank* GetControlledTank() const;
	ATank* GetPlayerTank() const;
};

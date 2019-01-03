// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("I am not possessing anything!"));
	}
	UE_LOG(LogTemp, Warning, TEXT("I am controlling %s!"), *(ControlledTank->GetName()));
}


ATank * ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

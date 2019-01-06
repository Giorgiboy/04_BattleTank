// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	auto playerTank =GetPlayerTank();
	if (!playerTank) {
		UE_LOG(LogTemp, Warning, TEXT("I am not possessing anything!"));
	}
	UE_LOG(LogTemp, Warning, TEXT("I found %s!"), *(playerTank->GetName()));
}

void ATankAIController::Tick(float DeltaTime){
	//GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
}

ATank * ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const {
	auto player = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!player) {
		return nullptr;
	}
	return Cast<ATank>(player);
}

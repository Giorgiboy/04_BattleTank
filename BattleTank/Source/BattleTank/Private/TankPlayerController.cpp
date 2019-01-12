// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Engine/World.h"

void ATankPlayerController::BeginPlay(){
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("I am not possessing anything!"));
	}
	UE_LOG(LogTemp, Warning, TEXT("I am controlling %s!"), *(ControlledTank->GetName()));
}

void ATankPlayerController::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair(){
	if (!GetControlledTank()) {
		return;
	}
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation)) {
		DrawDebugLine(GetWorld(), PlayerCameraManager->GetCameraLocation(), HitLocation, FColor::Red, false, 0.1, 1, 2);
		GetControlledTank()->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(OUT FVector& OutHitLocation) const{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	FVector LookDirection;

	if (GetCameraLookDirection(ScreenLocation, LookDirection)) {
		GetLookVectorHitLocation(LookDirection, OutHitLocation);
		return true;
	}
	return false;
}

bool ATankPlayerController::GetCameraLookDirection(FVector2D ScreenLocation, FVector & CameraLookDirection) const {
	FVector CameraWorldLocation;
	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, CameraLookDirection)) {
		return true;
	}
	return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector CameraLookDirection, FVector & HitLocation) const{

	FHitResult HitResult;
	auto StartingPoint = PlayerCameraManager->GetCameraLocation();
	auto EndingPoint = StartingPoint + CameraLookDirection * LineTraceRange;

	if(GetWorld()->LineTraceSingleByChannel(HitResult, StartingPoint, EndingPoint, ECC_Visibility)) {
		HitLocation = HitResult.Location;
		return true;
	}
	return false;
}

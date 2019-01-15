// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankAimingComponent.h"

// Sets default values
ATank::ATank(){
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay(){
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent){
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector TargetLocation){
	TankAimingComponent->AimAt(TargetLocation, LaunchSpeed);
}

void ATank::SetBarrelReference(UTankBarrel* BarrelReference){
	Barrel = BarrelReference;
	TankAimingComponent->SetBarrelReference(BarrelReference);
}

void ATank::SetTurretReference(UTankTurret * TurretReference){
	TankAimingComponent->SetTurretReference(TurretReference);
}

void ATank::Fire(){
	UE_LOG(LogTemp, Warning, TEXT("FIRE!!!"));
	GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
										Barrel->GetSocketLocation(FName("FiringPoint")),
										Barrel->GetSocketRotation(FName("FiringPoint"))
	);
}


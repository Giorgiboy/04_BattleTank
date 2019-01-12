// Fill out your copyright notice in the Description page of Project Settings.

#include	"TankAimingComponent.h"
#include	"GameFramework/Actor.h"
#include	"TankBarrel.h"
#include	"TankTurret.h"
#include	"Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include	"Runtime/Engine/Classes/Components/StaticMeshComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent(){
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelReference) {
	Barrel = BarrelReference;
}

void UTankAimingComponent::SetTurretReference(UTankTurret * TurretReference){
	Turret = TurretReference;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay(){
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector TargetLocation, float FiringSpeed){
	if (!Barrel) {
		return;
	}
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("FiringPoint"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		TargetLocation,
		FiringSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if (bHaveAimSolution) {
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelToward(AimDirection);
		auto Time = GetWorld()->TimeSeconds;
		//UE_LOG(LogTemp, Warning, TEXT("%f: I am aiming at %s"), Time, *AimDirection.ToString());
	}
	else {
		auto Time = GetWorld()->TimeSeconds;
		//UE_LOG(LogTemp, Warning, TEXT("%f: No solution found :("), Time);
	}
}

void UTankAimingComponent::MoveBarrelToward(FVector AimDirection){
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}


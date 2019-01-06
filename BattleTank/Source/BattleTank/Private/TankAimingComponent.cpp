// Fill out your copyright notice in the Description page of Project Settings.

#include	"TankAimingComponent.h"
#include	"GameFramework/Actor.h"
#include	"Runtime/Engine/Public/DrawDebugHelpers.h"
#include	"Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include	"Runtime/Engine/Classes/Components/StaticMeshComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent(){
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelReference) {
	Barrel = BarrelReference;
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
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if (bHaveAimSolution) {
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		DrawDebugLine(GetWorld(), StartLocation, (StartLocation + AimDirection * FiringSpeed), FColor::Red, false, 0.1f, 1);
		UE_LOG(LogTemp, Warning, TEXT("I am aiming at %s"),  *AimDirection.ToString());
	}	
}

void UTankAimingComponent::MoveBarrelToward(FVector AimDirection){
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
}


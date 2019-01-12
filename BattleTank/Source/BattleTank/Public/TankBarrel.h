// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * Wrapper for the Barrel, needed to change elevation and rotation; also holds data about maximum Rotation and Elevation per second
 */
UCLASS(meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	//Relative speed, -1 means maximum downward 
	void Elevate(float RelativeSpeed);

private: 
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 5;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevationInDegrees = 40;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevationInDegrees = 0;
};
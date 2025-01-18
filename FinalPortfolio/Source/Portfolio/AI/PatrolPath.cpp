// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolPath.h"

// Sets default values
APatrolPath::APatrolPath()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
}

// Called when the game starts or when spawned
void APatrolPath::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APatrolPath::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

USplineComponent* APatrolPath::GetSpline()
{
	return Spline;
}


// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PatrolPath.h"
#include "Components/ActorComponent.h"
#include "PatrolComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTFOLIO_API UPatrolComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPatrolComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Defulet")
	void UpdateLocation();
	UFUNCTION(BlueprintCallable, Category = "Defulet")
	void CalculateSetDistances();

private:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Defulet",meta=(AllowPrivateAccess=true))
	APatrolPath* PatrolPath;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Defulet",meta=(AllowPrivateAccess=true))
	FVector Location;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Defulet",meta=(AllowPrivateAccess=true))
	bool Reverse;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Defulet",meta=(AllowPrivateAccess=true))
	float Distance;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Defulet",meta=(AllowPrivateAccess=true))
	float PluseDistance;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Defulet",meta=(AllowPrivateAccess=true))
	float MinusDistance;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Defulet",meta=(AllowPrivateAccess=true))
	ACharacter* OwnerCharacter;
};

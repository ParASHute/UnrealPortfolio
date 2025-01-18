// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolComponent.h"

#include "AssetTypeCategories.h"
#include "VectorTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values for this component's properties
UPatrolComponent::UPatrolComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UPatrolComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
}


// Called every frame
void UPatrolComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPatrolComponent::UpdateLocation()
{
	CalculateSetDistances();
	
	if(IsValid(PatrolPath))
	{
		if (Reverse)
		{
			Distance = MinusDistance;
			
			if (Distance <= 0)
			{
				Distance = PatrolPath->GetSpline()->GetSplineLength();
				if (PatrolPath->GetSpline()->IsClosedLoop())
				{
					Location = PatrolPath->GetSpline()->GetLocationAtDistanceAlongSpline
						(Distance, ESplineCoordinateSpace::World);

					 UBlackboardComponent* Blackboard =
					 	OwnerCharacter->GetController()->FindComponentByClass<UBlackboardComponent>();
					Blackboard->SetValueAsVector("PatrolLocation", Location);
					
				}
				else
				{
					Reverse = false;
					Location = PatrolPath->GetSpline()->GetLocationAtDistanceAlongSpline
						(Distance, ESplineCoordinateSpace::World);

					UBlackboardComponent* Blackboard =
						OwnerCharacter->GetController()->FindComponentByClass<UBlackboardComponent>();
					Blackboard->SetValueAsVector("PatrolLocation", Location);
				}
			}
			else
			{
				Location = PatrolPath->GetSpline()->GetLocationAtDistanceAlongSpline
						(Distance, ESplineCoordinateSpace::World);

				UBlackboardComponent* Blackboard =
					OwnerCharacter->GetController()->FindComponentByClass<UBlackboardComponent>();
				Blackboard->SetValueAsVector("PatrolLocation", Location);
			}
		}
		else
		{
			Distance = PluseDistance;
			
			if (Distance >= PatrolPath->GetSpline()->GetSplineLength())
			{
				Distance = 0.0;
				if (PatrolPath->GetSpline()->IsClosedLoop())
				{
					Location = PatrolPath->GetSpline()->GetLocationAtDistanceAlongSpline
						(Distance, ESplineCoordinateSpace::World);

					UBlackboardComponent* Blackboard =
						OwnerCharacter->GetController()->FindComponentByClass<UBlackboardComponent>();
					Blackboard->SetValueAsVector("PatrolLocation", Location);
					
				}
				else
				{
					Reverse = true;
					Location = PatrolPath->GetSpline()->GetLocationAtDistanceAlongSpline
						(Distance, ESplineCoordinateSpace::World);

					UBlackboardComponent* Blackboard =
						OwnerCharacter->GetController()->FindComponentByClass<UBlackboardComponent>();
					Blackboard->SetValueAsVector("PatrolLocation", Location);
				}
			}
			else
			{
				Location = PatrolPath->GetSpline()->GetLocationAtDistanceAlongSpline
						(Distance, ESplineCoordinateSpace::World);

				UBlackboardComponent* Blackboard =
					OwnerCharacter->GetController()->FindComponentByClass<UBlackboardComponent>();
				Blackboard->SetValueAsVector("PatrolLocation", Location);
			}
		}
	}
}

void UPatrolComponent::CalculateSetDistances()
{
	float MaxWalkSpeed = OwnerCharacter->GetCharacterMovement()->GetMaxSpeed();
	PluseDistance = PluseDistance + GetWorld()->GetDeltaSeconds() * MaxWalkSpeed;
	MinusDistance = MinusDistance - GetWorld()->GetDeltaSeconds() * MaxWalkSpeed;
}


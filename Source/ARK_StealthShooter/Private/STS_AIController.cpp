// Fill out your copyright notice in the Description page of Project Settings.


#include "STS_AIController.h"
#include <STS_HealthComponent.h>

ETeamAttitude::Type ASTS_AIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	const AActor * OtherActor = &Other;
	return (USTS_HealthComponent::IsFriendly(GetPawn(), OtherActor)) ? ETeamAttitude::Friendly : ETeamAttitude::Hostile;
}

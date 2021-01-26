// Fill out your copyright notice in the Description page of Project Settings.


#include "STS_BaseCharacter.h"
#include "GameFramework/PawnMovementComponent.h"
#include <STS_Weapon.h>
#include <STS_HealthComponent.h>

// Sets default values
ASTS_BaseCharacter::ASTS_BaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;

	HealthComponent = CreateDefaultSubobject<USTS_HealthComponent>(TEXT("HealthComponent"));
}

void ASTS_BaseCharacter::StartFire()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->StartFire();
	}
}

void ASTS_BaseCharacter::StopFire()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->StopFire();
	}
}

void ASTS_BaseCharacter::OnHealthChanged(USTS_HealthComponent * HealthComp, float Health, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{

}

void ASTS_BaseCharacter::OnDeath(USTS_HealthComponent* HealthComp, class AController* InstigatedBy, AActor* Killer)
{
	StopFire();
	GetMovementComponent()->StopMovementImmediately();
	this->SetActorEnableCollision(false);
}

// Called when the game starts or when spawned
void ASTS_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (IsValid(StartingWeaponClass))
	{
		
		CurrentWeapon = GetWorld()->SpawnActor<ASTS_Weapon>(StartingWeaponClass, FVector::ZeroVector, FRotator::ZeroRotator);
		if (IsValid(CurrentWeapon))
		{
			CurrentWeapon->SetOwner(this);
			CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponSocketName);
		}
	}

	if (IsValid(HealthComponent))
	{
		HealthComponent->OnHealthChanged.AddDynamic(this, &ASTS_BaseCharacter::OnHealthChanged);
		HealthComponent->OnDeath.AddDynamic(this, &ASTS_BaseCharacter::OnDeath);
	}
}



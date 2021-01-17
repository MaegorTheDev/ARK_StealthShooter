// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STS_Weapon.generated.h"

class UStaticMeshComponent;
class UParticleSystem;

UCLASS()
class ARK_STEALTHSHOOTER_API ASTS_Weapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTS_Weapon();

	void StartFire();

	void StopFire();
	
protected:
	
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent * WeaponMesh;

	UPROPERTY(EditDefaultsOnly)
	float ShotDistance;

	UPROPERTY(EditDefaultsOnly)
	float ShotDamage;

	UPROPERTY(EditDefaultsOnly, meta = (ClampMin=0.1f))
	float RoundsPerMinute;

	UPROPERTY(EditDefaultsOnly)
	uint8 bDrawDebug : 1;

	FTimerHandle TimerHandle_AutoFire;

	float TimeBetweenShots;

	float LastFireTime;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditDefaultsOnly)
	UParticleSystem * MuzzleEffect;

	UPROPERTY(EditDefaultsOnly)
	UParticleSystem * TracerEffect;

	UPROPERTY(EditDefaultsOnly)
	UParticleSystem * ImpactEffect;

	UPROPERTY(EditDefaultsOnly)
	FName MuzzleSocketName;

	UPROPERTY(EditDefaultsOnly)
	FName TracerTargetName;

	void Fire();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};

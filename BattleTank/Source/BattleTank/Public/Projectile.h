// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	AProjectile();

protected:
	virtual void BeginPlay() override;

public:
	void Launch(float Speed);

private:
	UProjectileMovementComponent * ProjectileMovement = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent *CollisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UParticleSystemComponent *LaunchBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UParticleSystemComponent *ImpactBlast = nullptr;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};

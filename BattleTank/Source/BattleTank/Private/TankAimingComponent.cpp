#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankAimingComponent::AimAt(FVector HitLocation) const
{
	if (!ensure(Barrel))
	{
		return;
	}

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false, 0.0f, 0.0f, 
		ESuggestProjVelocityTraceOption::DoNotTrace);
	if (bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::Initialize(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	if (!BarrelToSet || !TurretToSet)
	{
		return;
	}

	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::Fire()
{
	bool bIsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (!ensure(Barrel))
	{
		return;
	}

	if (bIsReloaded)
	{
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile")));
		Projectile->Launch(LaunchSpeed);

		LastFireTime = FPlatformTime::Seconds();

		UE_LOG(LogTemp, Warning, TEXT("Fire: %f"), FPlatformTime::Seconds());
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) const
{
	if (!ensure(Barrel) || !ensure(Turret))
	{
		return;
	}

	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotation;

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}

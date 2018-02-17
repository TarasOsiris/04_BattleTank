#include "Tank.h"
#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h"

ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

void ATank::AimAt(FVector HitLocation) const
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}

void ATank::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("FIRE"));

	if (!Barrel)
	{
		return;
	}

	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
		Barrel->GetSocketLocation(FName("Projectile")), 
		Barrel->GetSocketRotation(FName("Projectile")));
	Projectile->Launch(LaunchSpeed);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


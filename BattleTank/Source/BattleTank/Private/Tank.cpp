#include "Tank.h"
#include "TankMovementComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h"

ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


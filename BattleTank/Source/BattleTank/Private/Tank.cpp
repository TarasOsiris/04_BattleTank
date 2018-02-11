#include "Tank.h"

ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATank::AimAt(FVector HitLocation)
{
	auto OurTankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s Aim at hit Location: %s"), *OurTankName, *HitLocation.ToString());
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


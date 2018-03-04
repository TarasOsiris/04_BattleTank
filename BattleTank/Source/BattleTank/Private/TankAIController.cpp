// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (!ensure(PlayerTank  && ControlledTank))
	{
		return;
	}

	MoveToActor(PlayerTank, AcceptanceRadius);

	auto AimingCoponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	AimingCoponent->AimAt(PlayerTank->GetActorLocation());
	if (AimingCoponent->GetFiringState() == EFiringState::Locked)
	{
		AimingCoponent->Fire();
	}
}

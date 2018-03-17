// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "Runtime/Engine/Classes/Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossesedTank = Cast<ATank>(InPawn);
		if (!ensure(PossesedTank))
		{
			return;
		}

		PossesedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (!ensure(PlayerTank && ControlledTank))
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

void ATankAIController::OnPossessedTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("DEATH"));
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankAimingComponent.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	ATank();
	void AimAt(FVector HitLocation) const;

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetBarrelReference(UStaticMeshComponent* BarrelToSet);

protected:
	UTankAimingComponent * TankAimingComponent = nullptr;

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = Firing)
		float LaunchSpeed = 100000;
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float Distance = FVector::Dist(Tank->GetActorLocation(), GetActorLocation());

	if (InFireRange())
	{
		TurnTurret(Tank->GetActorLocation());
	}
}

void ATower::CheckFireCondition()
{
	if (Tank == nullptr)
	{
		return;
	}

	if (InFireRange() && Tank->bAllive) 
	{
		Fire();
	}
}

bool ATower::InFireRange()
{
	if (Tank)
	{
		float Distance = FVector::Dist(Tank->GetActorLocation(), GetActorLocation());

		if (Distance < FireRange)
		{
			return true;
		}
	}

	return false;
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

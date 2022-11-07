// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FightAndWinGameMode.h"
#include "HealthComponent.generated.h"

class AController;
class AFightAndWinGameMode;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKGAME_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	AFightAndWinGameMode* GameMode;


private:
	UPROPERTY(EditAnywhere)
	float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere)
	float CurrentHealth = 0;

	UFUNCTION()
	void DamageTaken
	(
		AActor* DamagedActor,
		float Damage,
		const UDamageType* 
		DamageType,
		AController* Instigator,
		AActor* DamageCauser
	);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};

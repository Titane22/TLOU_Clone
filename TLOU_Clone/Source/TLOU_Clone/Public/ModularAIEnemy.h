// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ModularAIEnemy.generated.h"

UCLASS()
class TLOU_CLONE_API AModularAIEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AModularAIEnemy();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsChase = false;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetIsChase(bool b);

	UFUNCTION(BlueprintImplementableEvent)
	void StatusChanged();
};
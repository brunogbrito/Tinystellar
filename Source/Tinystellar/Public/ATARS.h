// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ATARS.generated.h"


class USceneComponent;

UCLASS()
class TINYSTELLAR_API AATARS : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AATARS();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Center;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* CS01;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* CS02;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* CS03;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* CS04;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* S01;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* S02;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* S03;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* S04;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

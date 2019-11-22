// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ATARS.generated.h"


class USceneComponent;
class USpringArmComponent;
class UCameraComponent;

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

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
	float SpringArmZoomIn;

	UPROPERTY(VisibleAnywhere)
	float SpringArmZoomOut;

	float SpringArmCurrentLenght;

	float WalkDistance;

	float SprintDistance;

	float CS01RotationValue;
	float CS02RotationValue;
	float CS03RotationValue;
	float CS04RotationValue;

	UPROPERTY()
	float CSRotationInterpSpeed;

	UPROPERTY(VisibleAnywhere)
	float SinRotationValue;

	UPROPERTY(VisibleAnywhere)
	float CosRotationValue;

	UPROPERTY(VisibleAnywhere)
	float CenterRotationSpeed;

	UPROPERTY(VisibleAnywhere)
	float Speed;

	UPROPERTY()
	bool bIsSprinting;


	/*** FUNCTIONS ***/

	UFUNCTION()
	void MoveForward(float Value);

	UFUNCTION()
	void MoveRight(float Value);

	UFUNCTION()
	void ZoomIn();

	UFUNCTION()
	void ZoomOut();

	UFUNCTION()
	void StartSprint();

	UFUNCTION()
	void StopSprint();

	UFUNCTION()
	void SetSpringArmLengh();

	UFUNCTION()
	void SetWalkDistance();

	UFUNCTION()
	void SetSprintDistance();

	UFUNCTION()
	void SetWalkingRotation();

	UFUNCTION()
	void SetSprintRotation();




public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

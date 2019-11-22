// Fill out your copyright notice in the Description page of Project Settings.


#include "ATARS.h"
#include "Components/SceneComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AATARS::AATARS()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxAcceleration = 1024.0f;
	GetCharacterMovement()->MaxWalkSpeed = 200.0f;

	bUseControllerRotationYaw = false;

	Center = CreateDefaultSubobject<USceneComponent>(TEXT("Center"));
	Center->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);

	CS01 = CreateDefaultSubobject<USceneComponent>(TEXT("CS01"));
	CS01->USceneComponent::AttachToComponent(Center, FAttachmentTransformRules::SnapToTargetIncludingScale);

	CS02 = CreateDefaultSubobject<USceneComponent>(TEXT("CS02"));
	CS02->USceneComponent::AttachToComponent(Center, FAttachmentTransformRules::SnapToTargetIncludingScale);

	CS03 = CreateDefaultSubobject<USceneComponent>(TEXT("CS03"));
	CS03->USceneComponent::AttachToComponent(Center, FAttachmentTransformRules::SnapToTargetIncludingScale);

	CS04 = CreateDefaultSubobject<USceneComponent>(TEXT("CS04"));
	CS04->USceneComponent::AttachToComponent(Center, FAttachmentTransformRules::SnapToTargetIncludingScale);

	S01 = CreateDefaultSubobject<USceneComponent>(TEXT("S01"));
	S01->USceneComponent::AttachToComponent(CS01, FAttachmentTransformRules::SnapToTargetIncludingScale);

	S02 = CreateDefaultSubobject<USceneComponent>(TEXT("S02"));
	S02->USceneComponent::AttachToComponent(CS02, FAttachmentTransformRules::SnapToTargetIncludingScale);

	S03 = CreateDefaultSubobject<USceneComponent>(TEXT("S03"));
	S03->USceneComponent::AttachToComponent(CS03, FAttachmentTransformRules::SnapToTargetIncludingScale);

	S04 = CreateDefaultSubobject<USceneComponent>(TEXT("S04"));
	S04->USceneComponent::AttachToComponent(CS04, FAttachmentTransformRules::SnapToTargetIncludingScale);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritYaw = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->AttachToComponent(SpringArm, FAttachmentTransformRules::SnapToTargetIncludingScale);
	Camera->FieldOfView = 24.0f;

	SpringArmZoomIn = 5500.0f;
	SpringArmZoomOut = 45000.0f;
	SpringArmCurrentLenght = SpringArmZoomIn;

	Speed = 0.125f;
	CenterRotationSpeed = 0.05f;
}

// Called when the game starts or when spawned
void AATARS::BeginPlay()
{
	Super::BeginPlay();
	
}

void AATARS::MoveForward(float Value)
{
	AddMovementInput(UKismetMathLibrary::GetForwardVector(FRotator(0.0f, 0.0f, GetControlRotation().Yaw)), Value, false);
}

void AATARS::MoveRight(float Value)
{
	AddMovementInput(UKismetMathLibrary::GetRightVector(FRotator(0.0f, 0.0f, GetControlRotation().Yaw)), Value, false);
}

void AATARS::ZoomIn()
{
	SpringArmCurrentLenght = SpringArmZoomIn;
}

void AATARS::ZoomOut()
{
	SpringArmCurrentLenght = SpringArmZoomOut;
}


void AATARS::StartSprint()
{

}

void AATARS::StopSprint()
{

}

// Called every frame
void AATARS::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetSpringArmLengh();
	SetWalkDistance();
	SetWalkingRotation();
	SetSprintRotation();
}

void AATARS::SetSpringArmLengh()
{
	SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, SpringArmCurrentLenght, UGameplayStatics::GetWorldDeltaSeconds(this), 5.0f);
}



void AATARS::SetWalkDistance()
{
	WalkDistance = WalkDistance + (UKismetMathLibrary::NormalizeToRange(GetVelocity().Size(), 0.0f, 300.0f) * Speed);
}

void AATARS::SetSprintDistance()
{
	SprintDistance = SprintDistance + (UKismetMathLibrary::NormalizeToRange(GetVelocity().Size(), 0.0f, 300.0f) * CenterRotationSpeed);
}

void AATARS::SetWalkingRotation()
{
	if (!bIsSprinting && GetVelocity().Size() != 0.0f)
	{
		SinRotationValue = FMath::FInterpTo(SinRotationValue, FMath::Lerp(0.0f, 20.0f, UKismetMathLibrary::Sin(WalkDistance)), UGameplayStatics::GetWorldDeltaSeconds(this), 10.0f);
		CosRotationValue = FMath::FInterpTo(CosRotationValue, FMath::Lerp(0.0f, 20.0f, UKismetMathLibrary::Cos(WalkDistance)), UGameplayStatics::GetWorldDeltaSeconds(this), 10.0f);	
	}
	else
	{
		SinRotationValue = FMath::FInterpTo(SinRotationValue, 0.5f, UGameplayStatics::GetWorldDeltaSeconds(this), 10.0f);
		CosRotationValue = FMath::FInterpTo(CosRotationValue, 0.5f, UGameplayStatics::GetWorldDeltaSeconds(this), 10.0f);
	}

	S01->SetRelativeRotation(FRotator(SinRotationValue, 0.0f, 0.0f));
	S04->SetRelativeRotation(FRotator(SinRotationValue, 0.0f, 0.0f));

	S02->SetRelativeRotation(FRotator(CosRotationValue, 0.0f, 0.0f));
	S03->SetRelativeRotation(FRotator(CosRotationValue, 0.0f, 0.0f));
}

void AATARS::SetSprintRotation()
{

}

// Called to bind functionality to input
void AATARS::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AATARS::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AATARS::MoveRight);

	PlayerInputComponent->BindAction("Zoom", IE_Pressed, this, &AATARS::ZoomOut);
	PlayerInputComponent->BindAction("Zoom", IE_Released, this, &AATARS::ZoomIn);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AATARS::StartSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AATARS::StopSprint);
}




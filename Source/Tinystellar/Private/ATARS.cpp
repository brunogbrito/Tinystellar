// Fill out your copyright notice in the Description page of Project Settings.


#include "ATARS.h"
#include "Components/SceneComponent.h"

// Sets default values
AATARS::AATARS()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Center = CreateDefaultSubobject<USceneComponent>(TEXT("Center"));

	CS01 = CreateDefaultSubobject<USceneComponent>(TEXT("CS01"));
	CS01->USceneComponent::AttachToComponent(Center, FAttachmentTransformRules::KeepRelativeTransform);

	CS02 = CreateDefaultSubobject<USceneComponent>(TEXT("CS02"));
	CS02->USceneComponent::AttachToComponent(Center, FAttachmentTransformRules::KeepRelativeTransform);

	CS03 = CreateDefaultSubobject<USceneComponent>(TEXT("CS03"));
	CS03->USceneComponent::AttachToComponent(Center, FAttachmentTransformRules::KeepRelativeTransform);

	CS04 = CreateDefaultSubobject<USceneComponent>(TEXT("CS04"));
	CS04->USceneComponent::AttachToComponent(Center, FAttachmentTransformRules::KeepRelativeTransform);

	S01 = CreateDefaultSubobject<USceneComponent>(TEXT("S01"));
	S01->USceneComponent::AttachToComponent(CS01, FAttachmentTransformRules::KeepRelativeTransform);

	S02 = CreateDefaultSubobject<USceneComponent>(TEXT("S02"));
	S02->USceneComponent::AttachToComponent(CS02, FAttachmentTransformRules::KeepRelativeTransform);

	S03 = CreateDefaultSubobject<USceneComponent>(TEXT("S03"));
	S03->USceneComponent::AttachToComponent(CS03, FAttachmentTransformRules::KeepRelativeTransform);

	S04 = CreateDefaultSubobject<USceneComponent>(TEXT("S04"));
	S04->USceneComponent::AttachToComponent(CS04, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned
void AATARS::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AATARS::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AATARS::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


// Fill out your copyright notice in the Description page of Project Settings.


#include "ATsunami.h"
#include "Components\StaticMeshComponent.h"
#include "Materials/MaterialInterface.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Kismet/KismetRenderingLibrary.h"


// Sets default values
AATsunami::AATsunami()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	WaveAnimation = -50.0f;

}

// Called when the game starts or when spawned
void AATsunami::BeginPlay()
{
	Super::BeginPlay();
}

void AATsunami::OnConstruction(const FTransform& Transform)
{
	StaticMesh->SetStaticMesh(WaterMesh);
	TsunamiMaterialInstance = StaticMesh->CreateDynamicMaterialInstance(0, TsunamiMaterial, NAME_None);
	StaticMesh->SetMaterial(0, TsunamiMaterialInstance);
}

// Called every frame
void AATsunami::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


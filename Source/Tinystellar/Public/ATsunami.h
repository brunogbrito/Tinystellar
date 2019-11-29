// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ATsunami.generated.h"

class UStaticMeshComponent;
class UMaterialInstance;
class UMaterialInstanceDynamic;
class UTextureRenderTarget2D;

UCLASS()
class TINYSTELLAR_API AATsunami : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AATsunami();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(BlueprintReadWrite, Category = "Animation")
	float WaveAnimation;

	UPROPERTY(EditAnywhere, Category = "Mesh")
	UMaterialInterface* TsunamiMaterial;

	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMesh* WaterMesh;

	UPROPERTY(EditAnywhere, Category = "Mesh")
	UMaterialInstanceDynamic* TsunamiMaterialInstance;

	UPROPERTY(BlueprintReadWrite, Category = "Mesh")
	UTextureRenderTarget2D* Height0;

	UPROPERTY(BlueprintReadWrite, Category = "Mesh")
	UTextureRenderTarget2D* Height1;

	UPROPERTY(BlueprintReadWrite, Category = "Mesh")
	UTextureRenderTarget2D* Height2;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/AudioComponent.h"
#include "Components/SceneComponent.h"
#include "AMusicManager.generated.h"

class UAudioComponent;

UENUM(BlueprintType)
enum class TrackStage : uint8
{
	TS_Track1,
	TS_Track2,
	TS_Track3
};

UENUM(BlueprintType)
enum class TrackIntensity : uint8
{
	TS_Intensity1,
	TS_Intensity2,
	TS_Intensity3
};

UENUM(BlueprintType)
enum class TrackLayerSelection : uint8
{
	T1L1,
	T1L2,
	T1L3,
	T1L4,
	T1L5,
	T1L6,
	T1Rise,


	T2L1,
	T2L2,

	T3L1
};

UCLASS()
class TINYSTELLAR_API AAMusicManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAMusicManager();

	UPROPERTY()
	USceneComponent* SceneComp;

	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	TrackStage TrackStageState;

	/*** TRACKS STAGE 1 ***/
	UPROPERTY(EditAnywhere)
	UAudioComponent* T1AudioCompLayer1;
	UPROPERTY(EditAnywhere)
	UAudioComponent* T1AudioCompLayer2;
	UPROPERTY(EditAnywhere)
	UAudioComponent* T1AudioCompLayer3;
	UPROPERTY(EditAnywhere)
	UAudioComponent* T1AudioCompLayer4;
	UPROPERTY(EditAnywhere)
	UAudioComponent* T1AudioCompLayer5;
	UPROPERTY(EditAnywhere)
	UAudioComponent* T1AudioCompLayer6;
	UPROPERTY(EditAnywhere)
	UAudioComponent* T1AudioCompRise;

	/*** TRACKS STAGE 2 ***/
	UPROPERTY(EditAnywhere)
	UAudioComponent* T2AudioCompLayer1;
	UPROPERTY(EditAnywhere)
	UAudioComponent* T2AudioCompLayer2;

	/*** TRACKS STAGE 3 ***/
	UPROPERTY(EditDefaultsOnly)
	UAudioComponent* T3AudioCompLayer1;


	/*** TRANSITIONS ***/
	UPROPERTY(EditAnywhere, Category = "Audio")
	UAudioComponent* TransitionAudioCompLayer1;
	UPROPERTY(EditAnywhere, Category = "Audio")
	UAudioComponent* TransitionAudioCompLayer2;

	float MinVolume = 0.0003f;
	float MaxVolume = 0.8f;

	UPROPERTY(EditDefaultsOnly, Category = "Values")
		float MinVolumeCheck = 0.01f;

	float FadeInSpeed = 0.35f;
	float FadeOutSpeed = 0.9f;

	float TransitionFadeInSpeed = 0.35f;
	float TransitionFadeOutSpeed = 0.45f;

	UPROPERTY()
	bool T1bLayer1 = false;
	UPROPERTY()
	bool T1bLayer2 = false;
	UPROPERTY()
	bool T1bLayer3 = false;
	UPROPERTY()
	bool T1bLayer4 = false;
	UPROPERTY()
	bool T1bLayer5 = false;
	UPROPERTY()
	bool T1bLayer6 = false;
	UPROPERTY()
	bool T1bRise = false;

	UPROPERTY()
	bool T2bLayer1 = false;
	UPROPERTY()
	bool T2bLayer2 = false;

	UPROPERTY()
	bool T3bLayer1 = false;


	UPROPERTY()
	bool TransitionL1 = false;
	UPROPERTY()
	bool TransitionL2 = false;

	UFUNCTION()
	void FadeInAudioLayer(UAudioComponent* AudioComp, float DeltaTime, float FadeSpeed);

	UFUNCTION()
	void FadeOutAudioLayer(UAudioComponent* AudioComp, float DeltaTime, float FadeSpeed);

	UFUNCTION()
	void InitializePlay();

	UFUNCTION()
	void ChangeTrackStage(TrackStage NewStage, TrackIntensity TrackIntensityState);

	UFUNCTION()
	void StopLayerOnMinVolCheck();

	UFUNCTION()
	void FadeLayer(bool bCheck, TrackLayerSelection SelectedTrack);

	UFUNCTION()
	void VolumeUpdater(float DeltaTime);

	UFUNCTION()
	void TransitionBoolSetTrackTwo();

	UFUNCTION()
	void TransitionToTrackTwo();

	UFUNCTION()
	void InitiateTrackTwo();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

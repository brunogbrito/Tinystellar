// Fill out your copyright notice in the Description page of Project Settings.

#include "Math/UnrealMathUtility.h"
#include "TimerManager.h"
#include "AMusicManager.h"

// Sets default values
AAMusicManager::AAMusicManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));

	/*** TRACKS STAGE 1 ***/
	T1AudioCompLayer1 = CreateDefaultSubobject<UAudioComponent>(TEXT("T1AudioComp"));
	T1AudioCompLayer1->SetupAttachment(SceneComp);
	T1AudioCompLayer1->VolumeMultiplier = MinVolume;
	T1AudioCompLayer1->bAutoActivate = false;

	T1AudioCompLayer2 = CreateDefaultSubobject<UAudioComponent>(TEXT("T1AudioComp2"));
	T1AudioCompLayer2->SetupAttachment(SceneComp);
	T1AudioCompLayer2->VolumeMultiplier = MinVolume;
	T1AudioCompLayer2->bAutoActivate = false;

	T1AudioCompLayer3 = CreateDefaultSubobject<UAudioComponent>(TEXT("T1AudioComp3"));
	T1AudioCompLayer3->SetupAttachment(SceneComp);
	T1AudioCompLayer3->VolumeMultiplier = MinVolume;
	T1AudioCompLayer3->bAutoActivate = false;

	T1AudioCompLayer4 = CreateDefaultSubobject<UAudioComponent>(TEXT("T1AudioComp4"));
	T1AudioCompLayer4->SetupAttachment(SceneComp);
	T1AudioCompLayer4->VolumeMultiplier = MinVolume;
	T1AudioCompLayer4->bAutoActivate = false;

	T1AudioCompLayer5 = CreateDefaultSubobject<UAudioComponent>(TEXT("T1AudioComp5"));
	T1AudioCompLayer5->SetupAttachment(SceneComp);
	T1AudioCompLayer5->VolumeMultiplier = MinVolume;
	T1AudioCompLayer5->bAutoActivate = false;

	T1AudioCompLayer6 = CreateDefaultSubobject<UAudioComponent>(TEXT("T1AudioComp6"));
	T1AudioCompLayer6->SetupAttachment(SceneComp);
	T1AudioCompLayer6->VolumeMultiplier = MinVolume;
	T1AudioCompLayer6->bAutoActivate = false;

	T1AudioCompRise = CreateDefaultSubobject<UAudioComponent>(TEXT("T1AudioCompRiser"));
	T1AudioCompRise->SetupAttachment(SceneComp);
	T1AudioCompRise->VolumeMultiplier = MinVolume;
	T1AudioCompRise->bAutoActivate = false;

	/*** TRACKS STAGE 2 ***/
	T2AudioCompLayer1 = CreateDefaultSubobject<UAudioComponent>(TEXT("T2AudioComp1"));
	T2AudioCompLayer1->SetupAttachment(SceneComp);
	T2AudioCompLayer1->VolumeMultiplier = MaxVolume;
	T2AudioCompLayer1->bAutoActivate = false;

	T2AudioCompLayer2 = CreateDefaultSubobject<UAudioComponent>(TEXT("T2AudioComp2"));
	T2AudioCompLayer2->SetupAttachment(SceneComp);
	T2AudioCompLayer2->VolumeMultiplier = MaxVolume;
	T2AudioCompLayer2->bAutoActivate = false;

	/*** TRACKS STAGE 3 ***/
	T3AudioCompLayer1 = CreateDefaultSubobject<UAudioComponent>(TEXT("T3AudioComp1"));
	T3AudioCompLayer1->SetupAttachment(SceneComp);
	T3AudioCompLayer1->VolumeMultiplier = MinVolume;
	T3AudioCompLayer1->bAutoActivate = false;

	/*** TRANSITIONS ***/

	TransitionAudioCompLayer1 = CreateDefaultSubobject<UAudioComponent>(TEXT("TransitionAudioComp1"));
	TransitionAudioCompLayer1->SetupAttachment(SceneComp);
	TransitionAudioCompLayer1->VolumeMultiplier = MinVolume;
	TransitionAudioCompLayer1->bAutoActivate = false;

	TransitionAudioCompLayer2 = CreateDefaultSubobject<UAudioComponent>(TEXT("TransitionAudioComp2"));
	TransitionAudioCompLayer2->SetupAttachment(SceneComp);
	TransitionAudioCompLayer2->VolumeMultiplier = MinVolume;
	TransitionAudioCompLayer2->bAutoActivate = false;

}


void AAMusicManager::FadeInAudioLayer(UAudioComponent* AudioComp, float DeltaTime, float FadeSpeed)
{
	AudioComp->VolumeMultiplier = FMath::FInterpTo(AudioComp->VolumeMultiplier, MaxVolume, DeltaTime, FadeSpeed);
	AudioComp->SetVolumeMultiplier(AudioComp->VolumeMultiplier);
}

void AAMusicManager::FadeOutAudioLayer(UAudioComponent* AudioComp, float DeltaTime, float FadeSpeed)
{
	AudioComp->VolumeMultiplier = FMath::FInterpTo(AudioComp->VolumeMultiplier, MinVolume, DeltaTime, FadeSpeed);
	AudioComp->SetVolumeMultiplier(AudioComp->VolumeMultiplier);
}

void AAMusicManager::InitializePlay()
{
	//layer 8 is independent
	T1AudioCompRise->Play();

	switch (TrackStageState)
	{
	case TrackStage::TS_Track1:
		T1AudioCompLayer1->Play();
		T1AudioCompLayer2->Play();
		T1AudioCompLayer3->Play();
		T1AudioCompLayer4->Play();
		T1AudioCompLayer5->Play();
		T1AudioCompLayer6->Play();
		break;

	case TrackStage::TS_Track2:
		T2AudioCompLayer1->Play();
		T2AudioCompLayer2->Play();
		break;

	case TrackStage::TS_Track3:
		T3AudioCompLayer1->Play();
		break;
	}
}

void AAMusicManager::ChangeTrackStage(TrackStage NewStage, TrackIntensity TrackIntensityState)
{
	TrackStageState = NewStage;

	//based on track change stage, change layer booleans to fade in

	switch (NewStage)
	{
	case TrackStage::TS_Track1:

		//set other booleans to false so they fade out
		T2bLayer1 = false;
		T2bLayer2 = false;

		T3bLayer1 = false;

		//based on track intensity, set certain layers to true when track stage is initiated
		switch (TrackIntensityState)
		{
		case TrackIntensity::TS_Intensity1:
			T1bLayer1 = true;
			T1bLayer2 = true;
			break;

		case TrackIntensity::TS_Intensity2:
			T1bLayer3 = true;
			T1bLayer4 = true;
			break;

		case TrackIntensity::TS_Intensity3:
			T1bLayer5 = true;
			T1bLayer6 = true;
			T1bRise = true;

			break;
		}

		T1AudioCompLayer1->Play();
		T1AudioCompLayer2->Play();
		T1AudioCompLayer3->Play();
		T1AudioCompLayer4->Play();
		T1AudioCompLayer5->Play();
		T1AudioCompLayer6->Play();

		break;

	case TrackStage::TS_Track2:

		//set other booleans to false so they fade out
		T1bLayer1 = false;
		T1bLayer2 = false;
		T1bLayer3 = false;
		T1bLayer4 = false;
		T1bLayer5 = false;
		T1bLayer6 = false;

		T3bLayer1 = false;

		//based on track intensity, set certain layers to true when track stage is initiated
		switch (TrackIntensityState)
		{
		case TrackIntensity::TS_Intensity1:
			T2bLayer1 = true;
			break;

		case TrackIntensity::TS_Intensity2:
			T2bLayer1 = true;
			T2bLayer2 = true;
			break;

		case TrackIntensity::TS_Intensity3:
			T2bLayer1 = true;
			T2bLayer2 = true;
			break;
		}

		AAMusicManager::TransitionToTrackTwo();
		//special transition function required

		break;

	case TrackStage::TS_Track3:

		//set other booleans to false so they fade out
		T1bLayer1 = false;
		T1bLayer2 = false;
		T1bLayer3 = false;
		T1bLayer4 = false;
		T1bLayer5 = false;
		T1bLayer6 = false;

		T2bLayer1 = false;
		T2bLayer2 = false;

		//no track stages required as of yet
		T3bLayer1 = true;

		T3AudioCompLayer1->Play();

		break;
	}
}

void AAMusicManager::FadeLayer(bool bCheck, TrackLayerSelection SelectedTrack)
{
	switch (SelectedTrack)
	{
	case TrackLayerSelection::T1L1:
		T1bLayer1 = bCheck;
		break;
	case TrackLayerSelection::T1L2:
		T1bLayer2 = bCheck;
		break;
	case TrackLayerSelection::T1L3:
		T1bLayer3 = bCheck;
		break;
	case TrackLayerSelection::T1L4:
		T1bLayer4 = bCheck;
		break;
	case TrackLayerSelection::T1L5:
		T1bLayer5 = bCheck;
		break;
	case TrackLayerSelection::T1L6:
		T1bLayer6 = bCheck;
		break;
	case TrackLayerSelection::T1Rise:
		T1bRise = bCheck;
		break;

	case TrackLayerSelection::T2L1:
		T2bLayer1 = bCheck;
		break;
	case TrackLayerSelection::T2L2:
		T2bLayer2 = bCheck;
		break;

	case TrackLayerSelection::T3L1:
		T3bLayer1 = bCheck;
		break;
	}
}

void AAMusicManager::VolumeUpdater(float DeltaTime)
{
	//Controls layer fades based on bool
	//if in appropriate track stage, then fades in, otherwise does not -> placed as a security measure

	if (TrackStageState == TrackStage::TS_Track1)
	{
		if (T1bLayer1)
			AAMusicManager::FadeInAudioLayer(T1AudioCompLayer1, DeltaTime, FadeInSpeed);
		else
			AAMusicManager::FadeOutAudioLayer(T1AudioCompLayer1, DeltaTime, FadeOutSpeed);

		if (T1bLayer2)
			AAMusicManager::FadeInAudioLayer(T1AudioCompLayer2, DeltaTime, FadeInSpeed);
		else
			AAMusicManager::FadeOutAudioLayer(T1AudioCompLayer2, DeltaTime, FadeOutSpeed);

		if (T1bLayer3)
			AAMusicManager::FadeInAudioLayer(T1AudioCompLayer3, DeltaTime, FadeInSpeed);
		else
			AAMusicManager::FadeOutAudioLayer(T1AudioCompLayer3, DeltaTime, FadeOutSpeed);

		if (T1bLayer4)
			AAMusicManager::FadeInAudioLayer(T1AudioCompLayer4, DeltaTime, FadeInSpeed);
		else
			AAMusicManager::FadeOutAudioLayer(T1AudioCompLayer4, DeltaTime, FadeOutSpeed);

		if (T1bLayer5)
			AAMusicManager::FadeInAudioLayer(T1AudioCompLayer5, DeltaTime, FadeInSpeed);
		else
			AAMusicManager::FadeOutAudioLayer(T1AudioCompLayer5, DeltaTime, FadeOutSpeed);

		if (T1bLayer6)
			AAMusicManager::FadeInAudioLayer(T1AudioCompLayer6, DeltaTime, FadeInSpeed);
		else
			AAMusicManager::FadeOutAudioLayer(T1AudioCompLayer6, DeltaTime, FadeOutSpeed);

		if (T1bRise)
			AAMusicManager::FadeInAudioLayer(T1AudioCompRise, DeltaTime, FadeInSpeed);
		else
			AAMusicManager::FadeOutAudioLayer(T1AudioCompRise, DeltaTime, FadeOutSpeed);
	}
	else
	{
		AAMusicManager::FadeOutAudioLayer(T1AudioCompLayer1, DeltaTime, FadeOutSpeed);
		AAMusicManager::FadeOutAudioLayer(T1AudioCompLayer2, DeltaTime, FadeOutSpeed);
		AAMusicManager::FadeOutAudioLayer(T1AudioCompLayer3, DeltaTime, FadeOutSpeed);
		AAMusicManager::FadeOutAudioLayer(T1AudioCompLayer4, DeltaTime, FadeOutSpeed);
		AAMusicManager::FadeOutAudioLayer(T1AudioCompLayer5, DeltaTime, FadeOutSpeed);
		AAMusicManager::FadeOutAudioLayer(T1AudioCompLayer6, DeltaTime, FadeOutSpeed);
		AAMusicManager::FadeOutAudioLayer(T1AudioCompRise, DeltaTime, FadeOutSpeed);
	}



	if (TrackStageState == TrackStage::TS_Track2)
	{
		if (T2bLayer1)
			AAMusicManager::FadeInAudioLayer(T2AudioCompLayer1, DeltaTime, FadeInSpeed);
		else
			AAMusicManager::FadeOutAudioLayer(T2AudioCompLayer1, DeltaTime, FadeOutSpeed);

		if (T2bLayer2)
			AAMusicManager::FadeInAudioLayer(T2AudioCompLayer2, DeltaTime, FadeInSpeed);
		else
			AAMusicManager::FadeOutAudioLayer(T2AudioCompLayer2, DeltaTime, FadeOutSpeed);
	}
	else
	{
		AAMusicManager::FadeOutAudioLayer(T2AudioCompLayer1, DeltaTime, FadeOutSpeed);
		AAMusicManager::FadeOutAudioLayer(T2AudioCompLayer2, DeltaTime, FadeOutSpeed);
	}


	if (TrackStageState == TrackStage::TS_Track3)
	{
		if (T3bLayer1)
			AAMusicManager::FadeInAudioLayer(T3AudioCompLayer1, DeltaTime, FadeInSpeed);
		else
			AAMusicManager::FadeOutAudioLayer(T3AudioCompLayer1, DeltaTime, FadeOutSpeed);
	}
	else
	{
		AAMusicManager::FadeOutAudioLayer(T3AudioCompLayer1, DeltaTime, FadeOutSpeed);
	}

	//layer 8 doesn't require a TrackStage and is independent


	//transition layers
	if (TransitionL1)
		AAMusicManager::FadeInAudioLayer(TransitionAudioCompLayer1, DeltaTime, TransitionFadeInSpeed);
	else
		AAMusicManager::FadeOutAudioLayer(TransitionAudioCompLayer1, DeltaTime, TransitionFadeOutSpeed);

	if (TransitionL2)
		AAMusicManager::FadeInAudioLayer(TransitionAudioCompLayer2, DeltaTime, TransitionFadeInSpeed);
	else
		AAMusicManager::FadeOutAudioLayer(TransitionAudioCompLayer2, DeltaTime, TransitionFadeOutSpeed);
}



void AAMusicManager::TransitionToTrackTwo()
{
	FTimerHandle TimeHandler1;
	FTimerHandle TimeHandler2;
	TransitionAudioCompLayer1->Play();
	TransitionAudioCompLayer2->Play();
	TransitionL1 = true;
	TransitionL2 = true;
	GetWorld()->GetTimerManager().SetTimer(TimeHandler1, this, &AAMusicManager::TransitionBoolSetTrackTwo, 1.45f, false);
	GetWorld()->GetTimerManager().SetTimer(TimeHandler2, this, &AAMusicManager::InitiateTrackTwo, 2.f, false);
	UE_LOG(LogTemp, Log, TEXT("Timer started"));
}

void AAMusicManager::TransitionBoolSetTrackTwo()
{
	TransitionL1 = false;
	TransitionL2 = false;
}

void AAMusicManager::InitiateTrackTwo()
{

	T2AudioCompLayer1->Play();
	T2AudioCompLayer2->Play();
	UE_LOG(LogTemp, Log, TEXT("Track 2 now playing"));

}

void AAMusicManager::StopLayerOnMinVolCheck()
{
	//sets layers to stop based on track stage selected

	switch (TrackStageState)
	{

	case TrackStage::TS_Track1:

		//stop tracks other than this one when vol below MinVolumeCheck
		if (T2AudioCompLayer1->VolumeMultiplier <= MinVolumeCheck)
			T2AudioCompLayer1->Stop();
		if (T2AudioCompLayer2->VolumeMultiplier <= MinVolumeCheck)
			T2AudioCompLayer2->Stop();

		if (T3AudioCompLayer1->VolumeMultiplier <= MinVolumeCheck)
			T3AudioCompLayer1->Stop();
		break;

	case TrackStage::TS_Track2:

		//stop tracks other than this one when vol below MinVolumeCheck
		if (T1AudioCompLayer1->VolumeMultiplier <= MinVolumeCheck)
			T1AudioCompLayer1->Stop();
		if (T1AudioCompLayer2->VolumeMultiplier <= MinVolumeCheck)
			T1AudioCompLayer2->Stop();
		if (T1AudioCompLayer3->VolumeMultiplier <= MinVolumeCheck)
			T1AudioCompLayer3->Stop();
		if (T1AudioCompLayer4->VolumeMultiplier <= MinVolumeCheck)
			T1AudioCompLayer4->Stop();
		if (T1AudioCompLayer5->VolumeMultiplier <= MinVolumeCheck)
			T1AudioCompLayer5->Stop();
		if (T1AudioCompLayer6->VolumeMultiplier <= MinVolumeCheck)
			T1AudioCompLayer6->Stop();
		//if (T1AudioCompRise->VolumeMultiplier <= MinVolumeCheck)
		//	T1AudioCompRise->Stop();

	/*	if (T1AudioCompLayer8->VolumeMultiplier <= MinVolumeCheck)
			T1AudioCompLayer8->Stop();*/


		if (T3AudioCompLayer1->VolumeMultiplier <= MinVolumeCheck)
			T3AudioCompLayer1->Stop();
		break;

	case TrackStage::TS_Track3:

		//stop tracks other than this one when vol below MinVolumeCheck
		if (T1AudioCompLayer1->VolumeMultiplier <= MinVolumeCheck)
			T1AudioCompLayer1->Stop();
		if (T1AudioCompLayer2->VolumeMultiplier <= MinVolumeCheck)
			T1AudioCompLayer2->Stop();
		if (T1AudioCompLayer3->VolumeMultiplier <= MinVolumeCheck)
			T1AudioCompLayer3->Stop();
		if (T1AudioCompLayer4->VolumeMultiplier <= MinVolumeCheck)
			T1AudioCompLayer4->Stop();
		if (T1AudioCompLayer5->VolumeMultiplier <= MinVolumeCheck)
			T1AudioCompLayer5->Stop();
		if (T1AudioCompLayer6->VolumeMultiplier <= MinVolumeCheck)
			T1AudioCompLayer6->Stop();

		if (T2AudioCompLayer1->VolumeMultiplier <= MinVolumeCheck)
			T2AudioCompLayer1->Stop();
		if (T2AudioCompLayer2->VolumeMultiplier <= MinVolumeCheck)
			T2AudioCompLayer2->Stop();

		break;
	}

}

// Called when the game starts or when spawned
void AAMusicManager::BeginPlay()
{
	Super::BeginPlay();

	TrackStageState = TrackStage::TS_Track1;
	//T1bLayer1 = true;

	AAMusicManager::InitializePlay();
}

// Called every frame
void AAMusicManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//sets volume transitions based on booleans

	//based on track stage, stops all other layers when volume is below a certain amount
	//AMusicManager::StopLayerOnMinVolCheck();

	AAMusicManager::VolumeUpdater(DeltaTime);

	//UE_LOG(LogTemp, Log, TEXT("Volume value = %f"), AudioCompLayer1->VolumeMultiplier);

}


#include "AWinTrigger.h"
#include "DrawDebugHelpers.h"
#include "Engine/Classes/Sound/SoundWave.h"
#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"

AWinTriggerBox::AWinTriggerBox()
{
	OnActorBeginOverlap.AddDynamic(this, &AWinTriggerBox::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &AWinTriggerBox::OnOverlapEnd);
}

void AWinTriggerBox::BeginPlay()
{
	Super::BeginPlay();
	
	DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Green, true, 10, 0, 5);
}

void AWinTriggerBox::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
	if (OtherActor && (OtherActor != this)) {
		UE_LOG(LogTemp, Warning, TEXT("You win !!!"));
		// add sound here fireworks
		//AWinTriggerBox::WinAudioComponent->SetSound(SoundFile);
		//AWinTriggerBox::WinAudioComponent->Play();
	}
}

void AWinTriggerBox::OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor)
{
	if (OtherActor && (OtherActor != this)) {
		UE_LOG(LogTemp, Warning, TEXT("Game over"));
		// exits the editor entirely
		UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
	}
}

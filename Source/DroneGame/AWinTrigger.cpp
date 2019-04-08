#include "AWinTrigger.h"
#include "DrawDebugHelpers.h"
#include "CoreMinimal.h"

AWinTriggerBox::AWinTriggerBox()
{
	OnActorBeginOverlap.AddDynamic(this, &AWinTriggerBox::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &AWinTriggerBox::OnOverlapEnd);
}

void AWinTriggerBox::BeginPlay()
{
	Super::BeginPlay();
	
	DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Purple, true, -1, 0, 5);
}

void AWinTriggerBox::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
	if (OtherActor && (OtherActor != this)) {
		UE_LOG(LogTemp, Warning, TEXT("You win !!!"));
	}
}

void AWinTriggerBox::OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor)
{
	if (OtherActor && (OtherActor != this)) {
		UE_LOG(LogTemp, Warning, TEXT("Game over"));
		// exits the editor entirely
		//FGenericPlatformMisc::RequestExit(false);
	}
}

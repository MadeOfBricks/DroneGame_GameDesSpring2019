#include "ALiftTrigger.h"
#include "DrawDebugHelpers.h"
#include "Engine/Classes/GameFramework/Actor.h"
#include "CoreMinimal.h"

ALiftTriggerBox::ALiftTriggerBox()
{
	OnActorBeginOverlap.AddDynamic(this, &ALiftTriggerBox::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &ALiftTriggerBox::OnOverlapEnd);
}

void ALiftTriggerBox::BeginPlay()
{
	Super::BeginPlay();
	
	DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Purple, true, -1, 0, 5);
}

void ALiftTriggerBox::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
	if (OtherActor && (OtherActor != this)) {
		UE_LOG(LogTemp, Warning, TEXT("Overlap begin"));
	}
}

void ALiftTriggerBox::OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor)
{
	if (OtherActor && (OtherActor != this)) {
		UE_LOG(LogTemp, Warning, TEXT("Overlap end"));
	}
}

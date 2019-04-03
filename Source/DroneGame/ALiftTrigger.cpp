#include "ALiftTrigger.h"
#include "DrawDebugHelpers.h"
#include "Engine/Classes/GameFramework/CharacterMovementComponent.h"
#include "Engine/Classes/GameFramework/Character.h"
#include "Engine/Classes/Components/PrimitiveComponent.h"
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
		// not working. may try to move actor to top of trigger box when overlap begins
		FVector impulseDir = OverlappedActor->GetActorLocation();
		//impulseDir.Z += 250.0;
		impulseDir.X = 0;
		impulseDir.Y = 0;
		GetCharacterMovement()->AddImpulse(impulseDir*100000, true);
	}
}

void ALiftTriggerBox::OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor)
{
	if (OtherActor && (OtherActor != this)) {
		UE_LOG(LogTemp, Warning, TEXT("Overlap end"));
	}
}

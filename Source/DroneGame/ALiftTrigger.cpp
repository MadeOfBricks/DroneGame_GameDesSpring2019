#include "ALiftTrigger.h"
#include "DrawDebugHelpers.h"
#include "Engine/Classes/GameFramework/CharacterMovementComponent.h"
#include "Engine/Classes/GameFramework/Character.h"
#include "Engine/Classes/GameFramework/Actor.h"
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
		FVector actorLocation = OverlappedActor->GetActorLocation();
		FVector newLocation = OverlappedActor->GetActorLocation();
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Original Z value from ACTOR: %f"), actorLocation.Z));
		newLocation.Z += 250000.0;
		SetActorLocation(newLocation, false);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Z value from SET: %f"), newLocation.Z));
		actorLocation = OverlappedActor->GetActorLocation();
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Z value from ACTOR: %f"), actorLocation.Z));
		//GetCharacterMovement()->AddImpulse(impulseDir*100000, true);
	}
}

void ALiftTriggerBox::OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor)
{
	if (OtherActor && (OtherActor != this)) {
		UE_LOG(LogTemp, Warning, TEXT("Overlap end"));
	}
}

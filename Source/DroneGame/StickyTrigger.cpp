// Fill out your copyright notice in the Description page of Project Settings.

#include "StickyTrigger.h"
#include "DrawDebugHelpers.h"
#include "Engine/Classes/GameFramework/Actor.h"
#include "CoreMinimal.h"
#include "FPSCharacter.h"

AStickyTrigger::AStickyTrigger()
{
	OnActorBeginOverlap.AddDynamic(this, &AStickyTrigger::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &AStickyTrigger::OnOverlapEnd);
}

void AStickyTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Purple, true, -1, 0, 5);
}

void AStickyTrigger::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
	if (OtherActor && (OtherActor != this)) {
		UE_LOG(LogTemp, Warning, TEXT("Overlap begin"));
		// not working. may try to move actor to top of trigger box when overlap begins
		//FVector newLocation = OverlappedActor->GetActorLocation();
		//newLocation.Z += 250000.0;
		//SetActorLocation(newLocation, false);
		AFPSCharacter *OverlappedCharacter = Cast<AFPSCharacter>(OtherActor);
		if (OverlappedCharacter != nullptr)
			OverlappedCharacter->Stick();
	    //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Cast didn't crash"), newLocation.Z));
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Z value from SET: %f"), newLocation.Z));
		//GetCharacterMovement()->AddImpulse(newLocation*100000, true);
	}
}

void AStickyTrigger::OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor)
{
	if (OtherActor && (OtherActor != this)) {
		UE_LOG(LogTemp, Warning, TEXT("Overlap end"));
	}
}


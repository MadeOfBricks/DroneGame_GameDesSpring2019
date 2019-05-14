// Fill out your copyright notice in the Description page of Project Settings.

#include "OnCollisionAsPawn.h"
#include "Components/BoxComponent.h"
#include "FPSCharacter.h"

// Sets default values
AOnCollisionAsPawn::AOnCollisionAsPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Use a sphere as simple collision representation
	MyComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	MyComp->SetSimulatePhysics(true);
	MyComp->SetNotifyRigidBodyCollision(true);

	MyComp->BodyInstance.SetCollisionProfileName("BlockAllDynamic");
	MyComp->OnComponentHit.AddDynamic(this, &AOnCollisionAsPawn::OnCompHit);

	// Set as root component
	RootComponent = MyComp;
}

// Called when the game starts or when spawned
void AOnCollisionAsPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOnCollisionAsPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AOnCollisionAsPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Called every frame
void AOnCollisionAsPawn::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, 
UPrimitiveComponent* OtherComp, FVector NormalImpulse
, const FHitResult& Hit){
	if ((OtherActor != NULL) && (OtherActor != this) 
	&& (OtherComp != NULL))
	{
		if (OtherActor->GetName() == "BPFPSCharacter_C_0")
			if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Gottem")));
			AFPSCharacter *PlayerActor = Cast<AFPSCharacter>(OtherActor);
			PlayerActor->ResetLevel();
		/*
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("I Hit: %s"), *OtherActor->GetName()));
		if ((*OtherActor->GetName()) == TEXT("BPFPSCharacter_C_0")){
			if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Gottem")));
		}
		*/
		
	}
}
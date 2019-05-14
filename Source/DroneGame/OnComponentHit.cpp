// Fill out your copyright notice in the Description page of Project Settings.

#include "OnComponentHit.h"
#include "Components/BoxComponent.h"

// Sets default values
AOnComponentHit::AOnComponentHit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Use a sphere as simple collision representation
	MyComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	MyComp->SetSimulatePhysics(true);
	MyComp->SetNotifyRigidBodyCollision(true);

	MyComp->BodyInstance.SetCollisionProfileName("BlockAllDynamic");
	MyComp->OnComponentHit.AddDynamic(this, &AOnComponentHit::OnCompHit);

	// Set as root component
	RootComponent = MyComp;

}

// Called when the game starts or when spawned
void AOnComponentHit::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOnComponentHit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called every frame
void AOnComponentHit::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, 
UPrimitiveComponent* OtherComp, FVector NormalImpulse
, const FHitResult& Hit){
	if ((OtherActor != NULL) && (OtherActor != this) 
	&& (OtherComp != NULL))
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("I Hit: %s"), *OtherActor->GetName()));
	}
}
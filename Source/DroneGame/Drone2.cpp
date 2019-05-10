// Fill out your copyright notice in the Description page of Project Settings.

#include "Drone2.h"

// Sets default values
ADrone2::ADrone2()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Use capsule as simple collision
	MyComp = GetCapsuleComponent();//CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapComp"));
	//MyComp->SetSimulatePhysics(true);
	MyComp->SetNotifyRigidBodyCollision(true);

	MyComp->BodyInstance.SetCollisionProfileName("BlockAllDynamic");
	//MyComp->OnComponentHit.AddDynamic(this,&ADrone2::OnCompHit);

	//Set as root component
	RootComponent = MyComp;

}

// Called when the game starts or when spawned
void ADrone2::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADrone2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*
	if (OnActorHit != NULL){
		UE_LOG(LogTemp, Warning, TEXT("Touch"));
	}
	*/

}

void ADrone2::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL)){
		UE_LOG(LogTemp, Warning, TEXT("Touch"));
	}
}



/*
void ADrone2::OnActorHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Touch"));
}
*/


/*
void ADrone2::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Hit!"))
}
*/

// Called to bind functionality to input
/*
void ADrone2::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
*/

void ADrone2::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
	if (OtherActor && (OtherActor != this)) {
		UE_LOG(LogTemp, Warning, TEXT("Touch"));
		
	}
}

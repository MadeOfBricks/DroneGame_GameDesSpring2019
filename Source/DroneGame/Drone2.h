// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Drone2.generated.h"

UCLASS()
class DRONEGAME_API ADrone2 : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADrone2();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* MyComp;

	UFUNCTION()
	void OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	

	//UFUNCTION()
	//void OnActorHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	


	//UFUNCTION()
	//void OnActorHit();

	//UPROPERTY(EditAnywhere)
	//USphereComponent* MySphere;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

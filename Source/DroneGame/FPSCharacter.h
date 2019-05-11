// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Runtime/Engine/Classes/Components/AudioComponent.h"
#include "Runtime/Engine/Classes/Sound/SoundCue.h"
#include "FPSCharacter.generated.h"

UCLASS()
class DRONEGAME_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	AFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	//Handles right-left input
	UFUNCTION()
	void MoveRight(float Value);

	//Sets jump flag when pressed
	UFUNCTION()
	void StartJump();

	//Sets jump flag when released
	UFUNCTION()
	void StopJump();

	// Move forward on alternating mouse clicks
	UFUNCTION()
	void FireLeft();
	UFUNCTION()
	void FireRight();

	// Enable crouching on s press, disable on release.
	UFUNCTION()
	void StartCrouch();
	UFUNCTION()
	void StopCrouch();

	UFUNCTION()
	void LaunchUp();

	UFUNCTION()
	void Grapple();

	UFUNCTION()
	void Stick();

	UFUNCTION()
   	void ResetLevel();

	//FPS Camera
	UPROPERTY(VisibleAnywhere)
    UCameraComponent* FPSCameraComponent;

	UPROPERTY(VisibleAnywhere)
	USoundCue* screamAudioCue;
	
	UPROPERTY(VisibleAnywhere)
	USoundCue* step1AudioCue;

	UPROPERTY(VisibleAnywhere)
	USoundCue* step2AudioCue;

	// FPS Mesh, visible only to the one that owns it
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
    USkeletalMeshComponent* FPSMesh;

	//Gun muzzle's offset from the camera location.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

	//Projectile class to spawn.
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AFPSProjectile> ProjectileClass;

	//Movement Component
	//UPROPERTY(EditAnywhere)
	//UCharacterMovementComponent* MovComponent = GetMovementComponent();

	//Force alternating mouse clicks
	enum MouseButton { LEFT, RIGHT, NONE };
	MouseButton lastClicked = NONE;
};
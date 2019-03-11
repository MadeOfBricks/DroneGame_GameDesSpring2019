// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSCharacter.h"
#include "FPSProjectile.h"
#include "Camera/CameraComponent.h"
#include "CoreMinimal.h"
#include <string>

// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create FPS cam component
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	//Attach cam component to capsule component
	FPSCameraComponent->SetupAttachment((USceneComponent*)GetCapsuleComponent());
	// Position the cam slightly above eyes
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f,0.0f,50.0f + BaseEyeHeight));
	// Allow pawn to control cam rotation
	FPSCameraComponent->bUsePawnControlRotation = true;

	//Create FPS Mesh component for owning player
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	//Only the owning player sees this mesh
	FPSMesh->SetOnlyOwnerSee(true);
	FPSMesh->SetupAttachment(FPSCameraComponent);
	//Disable some enivron shadowing to preserve the illusion of one mesh
	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;

	//The owning player doesn't see regular body mesh
	GetMesh()->SetOwnerNoSee(true);

}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (GEngine)
	{
		// Put up a debug message for five seconds. The -1 "Key" value (first argument) indicates that we will never need to update or refresh this message.
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using FPSCharacter."));
	}
	//The owning player doesn't see regular body mesh
	GetMesh()->SetOwnerNoSee(true);

}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!GetCharacterMovement()->IsFalling()){
		//bPressedJump = true;
	};

}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Set up 'movement' bindings
	PlayerInputComponent->BindAxis("MoveRight",this,&AFPSCharacter::MoveRight);

	//Set up 'look' binds
	PlayerInputComponent->BindAxis("Turn",this,&AFPSCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp",this,&AFPSCharacter::AddControllerPitchInput);

	//Set up 'action' bindings
	PlayerInputComponent->BindAction("Jump",IE_Pressed,this,&AFPSCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump",IE_Released,this,&AFPSCharacter::StopJump);

	PlayerInputComponent->BindAction("FireLeft",IE_Released,this,&AFPSCharacter::FireLeft);
	PlayerInputComponent->BindAction("FireRight",IE_Released,this,&AFPSCharacter::FireRight);
}

void AFPSCharacter::MoveRight(float Value){
	// Find out which way is "right" and record that the player wants to move that way.
    FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
    AddMovementInput(Direction, Value);
}


void AFPSCharacter::StartJump(){
	bPressedJump = true;
}

void AFPSCharacter::StopJump(){
	bPressedJump = false;
}

void AFPSCharacter::FireLeft()
{	
	bool validInput = false;
	if (lastClicked == NULL) {
		lastClicked = MouseButton::LEFT;
		validInput = true;
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Registered: left. Last clicked: null."));
	} else if (lastClicked == MouseButton::LEFT) {
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Registered: left. Last clicked: left."));
		validInput = false;
	} else if (lastClicked == MouseButton::RIGHT) { 
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Registered: left. Last clicked: right."));
		lastClicked = MouseButton::LEFT;
		validInput = true;
	} else {
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("This should never happen."));
	}
	if (validInput) {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Valid Input"));
		}
		FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
		GetCharacterMovement()->AddImpulse(Direction,false);

	} else
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Input invalid."));
}

void AFPSCharacter::FireRight()
{
	bool validInput = false;
	if (lastClicked == NULL) {
		lastClicked = MouseButton::RIGHT;
		validInput = true;
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Registered: right. Last clicked: null."));
	} else if (lastClicked == MouseButton::LEFT) {
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Registered: right. Last clicked: left."));
		lastClicked = MouseButton::RIGHT;
		validInput = true;
	} else if (lastClicked == MouseButton::RIGHT) {
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Registered: right. Last clicked: right."));
			validInput = false;
	} else {
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("This should never happen."));
	}
	if (validInput) {
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Input Valid."));
		FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
		GetCharacterMovement()->AddImpulse(Direction,false);
	} else
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Input invalid."));
}
	//Attempt to fire a projectile
	/*
	if(ProjectileClass)
	{
		//Get camera transform
		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation);

		//Transform MuzzleOffset from camera space to world space
		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);
		FRotator MuzzleRotation = CameraRotation;
		// Skew aim to be slightly upwards
		MuzzleRotation.Pitch += 10.0f;
		UWorld* World = GetWorld();
		if (World){
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;
			// Spawn projectile at muzzle
			AFPSProjectile* Projectile = World ->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation,MuzzleRotation,SpawnParams);
			if (Projectile){
				// Set initial projectile trajector
				FVector LaunchDirection = MuzzleRotation.Vector();
				Projectile->FireInDirection(LaunchDirection);
			}
		}

	}
	*/
// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSCharacter.h"
#include "Camera/CameraComponent.h"
#include "CoreMinimal.h"

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
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Set up 'movement' bindings
	PlayerInputComponent->BindAxis("MoveForward",this,&AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&AFPSCharacter::MoveRight);

	//Set up 'look' binds
	PlayerInputComponent->BindAxis("Turn",this,&AFPSCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp",this,&AFPSCharacter::AddControllerPitchInput);

	//Set up 'action' bindings
	PlayerInputComponent->BindAction("Jump",IE_Pressed,this,&AFPSCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump",IE_Released,this,&AFPSCharacter::StopJump);
}

void AFPSCharacter::MoveForward(float Value){
	// Find out which way is "forward" and record that the player wants to move that way.
    FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
    AddMovementInput(Direction, Value);
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
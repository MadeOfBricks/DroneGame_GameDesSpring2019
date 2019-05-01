// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSCharacter.h"
#include "FPSProjectile.h"
#include "Camera/CameraComponent.h"
#include "CoreMinimal.h"
#include <string>
#include "DrawDebugHelpers.h"


bool DEBUG = true;
bool SLIDING = false;
bool STUCK = false;

void debug(FColor color, const FString message) {
	if (GEngine && DEBUG)
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, color, message);
}

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
	debug(FColor::Green, FString("We are using FPSCharacter."));
	//The owning player doesn't see regular body mesh
	GetMesh()->SetOwnerNoSee(true);
	GetCharacterMovement()->JumpZVelocity = 400;

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

	PlayerInputComponent->BindAction("Crouch",IE_Pressed,this,&AFPSCharacter::StartCrouch);
	PlayerInputComponent->BindAction("Crouch",IE_Released,this,&AFPSCharacter::StopCrouch);

	PlayerInputComponent->BindAction("Grapple",IE_Pressed,this,&AFPSCharacter::Grapple);
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
	if (lastClicked == MouseButton::NONE) {
		lastClicked = MouseButton::LEFT;
		validInput = true;
		debug(FColor::Green, TEXT("Registered: left. Last clicked: none."));
	} else if (lastClicked == MouseButton::LEFT) {
		debug(FColor::Red, TEXT("Registered: left. Last clicked: left."));
		validInput = false;
	} else if (lastClicked == MouseButton::RIGHT) { 
		debug(FColor::Green, TEXT("Registered: left. Last clicked: right."));
		lastClicked = MouseButton::LEFT;
		validInput = true;
	} else {
		debug(FColor::Red, TEXT("This should never happen."));
	}
	if (validInput) {
		debug(FColor::Green, TEXT("Input Valid"));
		FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
		if (GetCharacterMovement()->Velocity.Z < 0)
			Direction.Z = 0;

		if (!SLIDING && !GetCharacterMovement()->IsFalling())
		    GetCharacterMovement()->Velocity = Direction*2000;
		else if (!SLIDING && STUCK) {
			GetCharacterMovement()->Velocity = Direction*3000;
			GetCharacterMovement()->GravityScale = 1.0;
			STUCK = false;
		}
		else if (!SLIDING)
			GetCharacterMovement()->Velocity = Direction*1000;
	} else
		debug(FColor::Red, TEXT("Input invalid."));
}

void AFPSCharacter::FireRight()
{
	bool validInput = false;
	if (lastClicked == MouseButton::NONE) {
		lastClicked = MouseButton::RIGHT;
		validInput = true;
		debug(FColor::Green, TEXT("Registered: right. Last clicked: none."));
	} else if (lastClicked == MouseButton::LEFT) {
		debug(FColor::Green, TEXT("Registered: right. Last clicked: left."));
		lastClicked = MouseButton::RIGHT;
		validInput = true;
	} else if (lastClicked == MouseButton::RIGHT) {
		debug(FColor::Red, TEXT("Registered: right. Last clicked: right."));
		validInput = false;
	} else {
		debug(FColor::Red, TEXT("This should never happen."));
	}
	if (validInput) {
		debug(FColor::Green, TEXT("Input Valid."));
		FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
		if (GetCharacterMovement()->Velocity.Z < 0)
			Direction.Z = 0;
		if (!SLIDING && !GetCharacterMovement()->IsFalling())
			GetCharacterMovement()->Velocity = Direction*2000;
		else if (!SLIDING && STUCK) {
			GetCharacterMovement()->Velocity = Direction*3000;
			GetCharacterMovement()->GravityScale = 1.0;
			STUCK = false;
		}
		else if (!SLIDING)
			GetCharacterMovement()->Velocity = Direction*1000;
	} else
	debug(FColor::Red, TEXT("Input invalid."));
}

void AFPSCharacter::StartCrouch()
{
	GetCharacterMovement()->Velocity *= 2;
	SLIDING = true;
	debug(FColor::Green, TEXT("Crouch Start"));
	GetCharacterMovement()->BrakingFriction = 0.1;		
	GetCharacterMovement()->GroundFriction = 0.1;		
	GetCharacterMovement()->bWantsToCrouch = true;
}

void AFPSCharacter::StopCrouch()
{
	SLIDING = false;
	debug(FColor::Green, TEXT("Crouch Stop"));
	GetCharacterMovement()->BrakingFriction = 2.0;
	GetCharacterMovement()->GroundFriction = 2.0;		
	GetCharacterMovement()->bWantsToCrouch = false;
}

void AFPSCharacter::LaunchUp()
{
	GetCharacterMovement()->AddImpulse(FVector(0,0,100000), false);
	debug(FColor::Green, TEXT("Launched character"));
}

void AFPSCharacter::Stick()
{
	GetCharacterMovement()->Velocity = FVector(0,0,0);
	GetCharacterMovement()->GravityScale = 0.0;
	debug(FColor::Green, TEXT("Player stuck"));
	STUCK = true;
}

void AFPSCharacter::Grapple()
{
	debug(FColor::Green, TEXT("Grappling called"));
	FVector startTrace = GetController()->GetPawn()->GetActorLocation();
	FVector endTrace = startTrace + GetControlRotation().Vector() * 2000;
	FHitResult HitData = FHitResult(ForceInit);
	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectTypes;
	//TraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel1));
	TraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel2));
	if (DEBUG) {
		DrawDebugLine(GetWorld(), startTrace, endTrace, FColor::Green, false, 1.0, 3, 5.0);
		// LaunchCharacter(GetActorLocation() - endTrace, false, false);
	}
	if (GetWorld()->LineTraceSingleByObjectType(HitData, startTrace, endTrace, TraceObjectTypes, NULL)) {
		debug(FColor::Green, TEXT("Trace Successful"));
		debug(FColor::Green, TEXT("Gravity weird"));
		GetCharacterMovement()->GravityScale = 0.001;
		FVector LaunchVector = HitData.Location - startTrace;
		LaunchVector.Z += 100;
		LaunchCharacter(LaunchVector, false, false);
		GetCharacterMovement()->GravityScale = 1;
		debug(FColor::Green, TEXT("Gravity normal"));
	}
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
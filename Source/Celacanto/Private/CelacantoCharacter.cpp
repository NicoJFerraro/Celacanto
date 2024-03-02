// Fill out your copyright notice in the Description page of Project Settings.


#include "CelacantoCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


ACelacantoCharacter::ACelacantoCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetMesh());
	CameraBoom->TargetArmLength = 600.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void ACelacantoCharacter::BeginPlay()
{
	Super::BeginPlay();	
}

void ACelacantoCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACelacantoCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACelacantoCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ACelacantoCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &ACelacantoCharacter::LookUp);
}

void ACelacantoCharacter::MoveForward(float Value)
{
	if (Controller != nullptr && Value != 0.f)
	{
		const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
		const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X));
		AddMovementInput(Direction, Value);
	}
}

void ACelacantoCharacter::MoveRight(float Value)
{
	if (Controller != nullptr && Value != 0.f)
	{
		const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
		const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y));
		AddMovementInput(Direction, Value);
	}
}

void ACelacantoCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void ACelacantoCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void ACelacantoCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


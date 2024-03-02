// Fill out your copyright notice in the Description page of Project Settings.

#include "CelacantoAnimInstance.h"
#include "CelacantoCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


void UCelacantoAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	CelacantoCharacter = Cast<ACelacantoCharacter>(TryGetPawnOwner());

}

void UCelacantoAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (CelacantoCharacter == nullptr)
	{
		CelacantoCharacter = Cast<ACelacantoCharacter>(TryGetPawnOwner());
	}

	if (CelacantoCharacter == nullptr) return;

	FVector Velocity = CelacantoCharacter->GetVelocity();
	Velocity.Z = 0.f;
	speed = Velocity.Size();

	is_in_air = CelacantoCharacter->GetCharacterMovement()->IsFalling();
	is_accelerating = CelacantoCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f ? true : false;
}

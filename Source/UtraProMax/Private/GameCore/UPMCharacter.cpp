// Fill out your copyright notice in the Description page of Project Settings.


#include "UtraProMax/Public/GameCore/UPMCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AUPMCharacter::AUPMCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("DefaultCameraArm"));
	CameraArm->SetupAttachment(RootComponent);
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("DefaultCamera"));
	CameraComponent->SetupAttachment(CameraArm, USpringArmComponent::SocketName);

	CameraArm->TargetArmLength = 160;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraArm->bUsePawnControlRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

// Called when the game starts or when spawned
void AUPMCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUPMCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AUPMCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 先添加IMC还是绑定IA不重要，因为IMC代表的只是一个从按键到Action的关系
	if (APlayerController* CurPlayerController = CastChecked<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(CurPlayerController->GetLocalPlayer()))
		{
			if (FundamentalMappingContext) {
				subsystem->AddMappingContext(FundamentalMappingContext, 100);
			}
		}
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (LookAction)
		{
			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AUPMCharacter::Look);
		}
		if (MoveAction)
		{
			EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered, this, &AUPMCharacter::Move);
		}
	}
}

void AUPMCharacter::Move(const FInputActionValue& InInputActionValue)
{
	FVector2D MoveValue = InInputActionValue.Get<FVector2D>();
	if (Controller)
	{
		FRotator ControllerRotator = Controller->GetControlRotation();
		const FRotator rotationYaw = { 0,ControllerRotator.Yaw,0 };
		const FVector forwardDirection = FRotationMatrix(rotationYaw).GetUnitAxis(EAxis::X);
		const FVector rightDirection = FRotationMatrix(rotationYaw).GetUnitAxis(EAxis::Y);

		AddMovementInput(forwardDirection, MoveValue.Y);
		AddMovementInput(rightDirection, MoveValue.X);
	}
}

void AUPMCharacter::Look(const FInputActionValue& InInputActionValue)
{
	FVector2D LookValue = InInputActionValue.Get<FVector2D>();
	if (Controller)
	{
		AddControllerYawInput(LookValue.X);
		AddControllerPitchInput(LookValue.Y);
	}
}


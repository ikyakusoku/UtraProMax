// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UPMCharacter.generated.h"


#pragma region Class Declare
class UInputMappingContext;
class UInputAction;
class UCameraComponent;
class USpringArmComponent;
struct FInputActionValue;
#pragma endregion Class Declare


UCLASS()
class UTRAPROMAX_API AUPMCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUPMCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	void Move(const FInputActionValue& InInputActionValue);

	void Look(const FInputActionValue& InInputActionValue);
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnhancedInput", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> FundamentalMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnhancedInput", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnhancedInput", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraArm;
};

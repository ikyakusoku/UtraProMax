// Fill out your copyright notice in the Description page of Project Settings.


#include "UtraProMax/Public/GameCore/MyClass.h"


// Sets default values
AMyClass::AMyClass()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyClass::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMyClass::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


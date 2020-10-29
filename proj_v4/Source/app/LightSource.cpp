// Fill out your copyright notice in the Description page of Project Settings.


#include "LightSource.h"
#include <iostream>

// Sets default values
ALightSource::ALightSource()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;	
	myLight = CreateDefaultSubobject<UDirectionalLightComponent>("myLight");
	
	
	
}

// Called when the game starts or when spawned
void ALightSource::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALightSource::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ALightSource::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


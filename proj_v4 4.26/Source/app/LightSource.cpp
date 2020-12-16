// Fill out your copyright notice in the Description page of Project Settings.


#include "LightSource.h"


// Sets default values
ALightSource::ALightSource()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	myLight = CreateDefaultSubobject<UDirectionalLightComponent>("myLight");

	this->myLight->SetLightColor(FLinearColor(246, 255, 236));
	this->myLight->SetIntensity(100);

}

// Called when the game starts or when spawned
void ALightSource::BeginPlay()
{
	Super::BeginPlay();
	//F6FFECFF

	//this->myLight->SetLightBrightness(30);
	//changeColor(0, 255, 0);

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

void ALightSource::changeIntensity(float value) {

	myLight->SetIntensity(value * 150);

}

bool ALightSource::setCoord_z(float value) {

	/*if (value > maxZ)
		return false;*/

	FVector location = this->GetActorLocation();
	location.Z = value;
	this->SetActorLocation(location);
	return true;

}

bool ALightSource::setCoord_y(float value) {

	FVector location = this->GetActorLocation();
	location.Y = value;
	this->SetActorLocation(location);
	return true;

}

bool ALightSource::setCoord_x(float value) {

	FVector location = this->GetActorLocation();
	location.X = value;
	this->SetActorLocation(location);
	return true;

}

void ALightSource::quickChange_rotation(float value) {

	float a = 360 * value;
	FRotator rotator(0, a, 0);

	FVector location = this->GetActorLocation();
	this->SetActorRotation(FQuat(rotator));

}


void ALightSource::changeColor(FString value) {

	this->myLight->SetLightColor(FColor::FromHex(value));
}

void ALightSource::changeAngle_x(float value) {

	FRotator rotation = this->GetActorRotation();
	rotation.Roll = value;
	this->SetActorRotation(rotation);

}

void ALightSource::changeAngle_y(float value) {

	FRotator rotation = this->GetActorRotation();
	rotation.Pitch = value;
	this->SetActorRotation(rotation);

}


void ALightSource::changeAngle_z(float value) {

	FRotator rotation = this->GetActorRotation();
	rotation.Yaw = value;
	this->SetActorRotation(rotation);

}

void ALightSource::setModelPoint(FVector model) {

	/*modelPoint.X = model.X;
	modelPoint.Y = model.Y;
	modelPoint.Z = model.Z;*/

	modelPoint.X = 0;
	modelPoint.Y = 0;
	modelPoint.Z = 0;

}
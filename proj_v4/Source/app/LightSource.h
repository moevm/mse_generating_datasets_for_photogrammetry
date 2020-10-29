// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/DirectionalLightComponent.h"
#include "Engine/DirectionalLight.h"
#include "Math/RotationTranslationMatrix.h"
#include "Math/RotationMatrix.h"
#include "LightSource.generated.h"


UCLASS()
class APP_API ALightSource : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ALightSource();

	void quickChange_rotation(float value) {

		float a = 3.6 * value;
		FRotator rotator(0, a, 0);	
		
		FRotationMatrix r_matr(rotator);
		r_matr.MakeFromZ(startPoint);

		
	}

	void quickChange_distance(float value) {

		FVector location = this->GetActorLocation();
		FVector guides_vector = FVector(modelPoint.X - location.X, modelPoint.Y - location.Y, modelPoint.Z - location.Z);

		//float maxLx, maxLy, maxLz;
		float L = 0.5;//зависит от value
		/*maxLx = () / modelPoint.X - location.X;
		maxLy = () / modelPoint.X - location.X;
		maxLz = () / modelPoint.X - location.X;*/
		
		//
		//L = 

		setCoord_x(location.X + guides_vector.X * L);
		setCoord_y(location.Y + guides_vector.Y * L);
		setCoord_z(location.Z + guides_vector.Z * L);


	}

	void quickChange_height(float value) {
		
		float newHeight = value * maxZ / 100.0f;
		setCoord_z(newHeight);

	}

	bool setCoord_x(float value) {

		FVector location = this->GetActorLocation();
		location.X = value;
		this->SetActorLocation(location);
		return true;

	}

	bool setCoord_y(float value) {

		FVector location = this->GetActorLocation();
		location.Y = value;
		this->SetActorLocation(location);
		return true;

	}

	bool setCoord_z(float value) {

		if (value > maxZ)
			return false;

		FVector location = this->GetActorLocation();
		location.Z = value;
		this->SetActorLocation(location);
		return true;

	}

	void changeIntensity(float brightness) {

		//пересчитать проценты в значения
		this->myLight->SetLightBrightness(brightness);

	}

	void changeColor(float r, float g, float b) {

		//возможно получаем цвет в 16ричной системе
		FLinearColor color;
		color.R = r;
		color.G = g;
		color.B = b;

		this->myLight->SetLightColor(color);
	}

	void changeAngle_x() {
	
	}
	void changeAngle_y() {
	
	}
	void changeAngle_z() {
	
	}
	void setModelPoint(FVector model) {

		modelPoint.X = model.X;
		modelPoint.Y = model.Y;
		modelPoint.Z = model.Z;

	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	FVector startPoint;
	FVector modelPoint;
	float maxZ, maxY, maxX;
	

		UPROPERTY(VisibleAnywhere)
			UDirectionalLightComponent* myLight;

};

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

	UFUNCTION(BlueprintCallable)
	void quickChange_rotation(float value) {

		float a = 3.6 * value;
		FRotator rotator(0, a, 0);	
		
		FRotationMatrix r_matr(rotator);
		r_matr.MakeFromZ(startPoint);

		
	}

	UFUNCTION(BlueprintCallable)
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

	UFUNCTION(BlueprintCallable)
	void quickChange_height(float value) {
		
		maxZ = 4000;
		float newHeight = value * maxZ;
		setCoord_z(newHeight);
		
	}

	UFUNCTION(BlueprintCallable)
		bool setCoord_x(float value);

	UFUNCTION(BlueprintCallable)
		bool setCoord_y(float value);

	UFUNCTION(BlueprintCallable)
		bool setCoord_z(float value);

	UFUNCTION(BlueprintCallable)
		void changeIntensity(float value); 

	UFUNCTION(BlueprintCallable)
		float getZ() const {
			FVector location = this->GetActorLocation();
			return location.Z;
		}

	UFUNCTION(BlueprintCallable)
	void changeColor(FString value) {		

		this->myLight->SetLightColor(FColor::FromHex(value));
	}

	UFUNCTION(BlueprintCallable)
		void changeAngle_x(float value);

	UFUNCTION(BlueprintCallable)
		void changeAngle_y(float value);

	UFUNCTION(BlueprintCallable)
		void changeAngle_z(float value);

	void setModelPoint(FVector model);

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

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
		void quickChange_rotation(float value);

	UFUNCTION(BlueprintCallable)
		void quickChange_distance(float value) {

		FVector location = this->GetActorLocation();

		float cur_dist = sqrt((location.X - modelPoint.X) * (location.X - modelPoint.X) + (location.Y - modelPoint.Y) * (location.Y - modelPoint.Y) + (location.Z - modelPoint.Z) * (location.Z - modelPoint.Z));
		float max_dist = 1000, min_dist = 0;

		float delta = value - (cur_dist / max_dist);
		FVector guides_vector = FVector(-modelPoint.X + location.X, -modelPoint.Y + location.Y, -modelPoint.Z + location.Z);
		float newX, newY, newZ;

		if (delta)//расстояние надо увеличивать cur_dist
		{

		}
		else//надо уменьшать cur_dist
		{
			guides_vector *= -1;

		}

		newX = guides_vector.X * delta + location.X;
		newY = guides_vector.Y * delta + location.Y;
		newZ = guides_vector.Z * delta + location.Z;

		setCoord_x(newX);
		setCoord_y(newY);
		setCoord_z(newZ);

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
		float getX() const {
		FVector location = this->GetActorLocation();
		return location.X;
	}

	UFUNCTION(BlueprintCallable)
		float getY() const {
		FVector location = this->GetActorLocation();
		return location.Y;
	}

	UFUNCTION(BlueprintCallable)
		float getAngleZ() const {
		FRotator rotation = this->GetActorRotation();
		return rotation.Yaw;
	}

	UFUNCTION(BlueprintCallable)
		float getAngleX() const {
		FRotator rotation = this->GetActorRotation();
		return rotation.Roll;
	}

	UFUNCTION(BlueprintCallable)
		float getAngleY() const {
		FRotator rotation = this->GetActorRotation();		
		return rotation.Pitch;
	}

	UFUNCTION(BlueprintCallable)
		FString getColorOfLight() const {
		return this->color;
	}

	UFUNCTION(BlueprintCallable)
		float getIntens() const {
		return this->intens;
	}


	UFUNCTION(BlueprintCallable)
		void changeColor(FString value);

	UFUNCTION(BlueprintCallable)
		void changeAngle_x(float value);

	UFUNCTION(BlueprintCallable)
		void changeAngle_y(float value);

	UFUNCTION(BlueprintCallable)
		void changeAngle_z(float value);

	UFUNCTION(BlueprintCallable)
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
	float intens;
	FString color;


	UPROPERTY(VisibleAnywhere)
		UDirectionalLightComponent* myLight;


};
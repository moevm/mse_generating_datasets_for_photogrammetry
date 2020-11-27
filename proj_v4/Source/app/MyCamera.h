// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "MyCamera.generated.h"

UCLASS()
class APP_API AMyCamera : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	bool upIt = false;
	bool downIt = false;
	bool leftIt = false;
	bool rightIt = false;
	bool ulIt = false;
	bool urIt = false;
	bool dlIt = false;
	bool drIt = false;
	bool randIt = false;
	bool playIt = false;

	float DesiredArmLength;
	FRotator endPos;
	FVector angleInput;
	FVector meshVector;
	FVector startPositionMesh = { 0.0f, 0.0f, 100.0f };

	UPROPERTY(EditAnywhere)
		USpringArmComponent* springArm;

	UCameraComponent* camera;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* mesh;

	UFUNCTION(BlueprintCallable)
		void SetCameraYaw(float axis);
	UFUNCTION(BlueprintCallable)
		void SetCameraPitch(float axis);
	UFUNCTION(BlueprintCallable)
		void SetCameraRoll(float axis);
	UFUNCTION(BlueprintCallable)
		void SetArmLenght(float axis);
	UFUNCTION(BlueprintCallable)
		void SetMeshVectorX(float axis);
	UFUNCTION(BlueprintCallable)
		void SetMeshVectorY(float axis);
	UFUNCTION(BlueprintCallable)
		void SetMeshVectorZ(float axis);

	UFUNCTION(BlueprintCallable)
		float GetViewAngleX();
	UFUNCTION(BlueprintCallable)
		float GetViewAngleY();
	UFUNCTION(BlueprintCallable)
		float GetViewAngleZ();
	UFUNCTION(BlueprintCallable)
		float GetMeshCoordX();
	UFUNCTION(BlueprintCallable)
		float GetMeshCoordY();
	UFUNCTION(BlueprintCallable)
		float GetMeshCoordZ();

	UFUNCTION(BlueprintCallable)
		void MoveCamera();
	UFUNCTION(BlueprintCallable)
		void StopMoveCamera();
	UFUNCTION(BlueprintCallable)
		void ToRight();
	UFUNCTION(BlueprintCallable)
		void ToLeft();
	UFUNCTION(BlueprintCallable)
		void ToUp();
	UFUNCTION(BlueprintCallable)
		void ToDown();
	UFUNCTION(BlueprintCallable)
		void ToUR();
	UFUNCTION(BlueprintCallable)
		void ToUL();
	UFUNCTION(BlueprintCallable)
		void ToDR();
	UFUNCTION(BlueprintCallable)
		void ToDL();
	UFUNCTION(BlueprintCallable)
		void ToRand();
	UFUNCTION(BlueprintCallable)
		void ToCancel();
};

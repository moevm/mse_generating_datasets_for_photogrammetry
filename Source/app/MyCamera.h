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
    float deltaOfAngle;
    float fullAngle;
    float screenCount;
    int numbers;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



	struct AspectRatioData {
	private:
		float width;
		float height;
		float imageAspectRatio;

	public:
		
		AspectRatioData() {
			width = 1920.0f;
			height = 1080.0f;
			imageAspectRatio = width / height;
		}

		void SetWidth(float axis) {
			width = axis;
		}

		void SetHeight(float axis) {
			height = axis;
		}

		void SetAspectRatio() {
			imageAspectRatio = width / height;
		}

		float GetWidth() {
			return width;
		}

		float GetHeight() {
			return height;
		}

		float GetAspectRatio()
		{
			return imageAspectRatio;
		}
	};

	AspectRatioData aspectRatioImage;

    bool upIt = false;
    bool downIt = false;
    bool leftIt = false;
    bool rightIt = false;
    bool ulIt = false;
    bool urIt = false;
    bool dlIt = false;
    bool drIt = false;
    bool stopIt = false;
    bool playIt = false;

	bool flagForRoll = false;
	bool flagForUpDown = false;
	bool flagForFinishMove = false;

    float DesiredArmLength;
    FRotator endPos;
    FVector angleInput;
    FVector meshVector;
    FVector startPositionMesh = { 0.0f, 0.0f, 100.0f };

	FPostProcessSettings PPSettings;
	

    UPROPERTY(EditAnywhere)
        USpringArmComponent* springArm;

	UPROPERTY(EditAnywhere)
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
		void SetISO(float axis);
	UFUNCTION(BlueprintCallable)
		void SetFocalDistance(float axis);
	UFUNCTION(BlueprintCallable)
		void SetFStop(float axis);
	UFUNCTION(BlueprintCallable)
		void SetMFStop(float axis);
	UFUNCTION(BlueprintCallable)
		void SetWhiteTemp(float axis);
	UFUNCTION(BlueprintCallable)
		void SetWhiteTint(float axis);
	UFUNCTION(BlueprintCallable)
		void SetAspectRatioWidth(float axis);
	UFUNCTION(BlueprintCallable)
		void SetAspectRatioHeight(float axis);
	UFUNCTION(BlueprintCallable)
		void SetAspectRatio();

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
		float GetArmLenght();
	UFUNCTION(BlueprintCallable)
		float GetISO();
	UFUNCTION(BlueprintCallable)
		float GetFocalDistance();
	UFUNCTION(BlueprintCallable)
		float GetFStop();
	UFUNCTION(BlueprintCallable)
		float GetMFStop();
	UFUNCTION(BlueprintCallable)
		float GetWhiteTemp( );
	UFUNCTION(BlueprintCallable)
		float GetWhiteTint( );
	UFUNCTION(BlueprintCallable)
		float GetAspectRatioWidth( );
	UFUNCTION(BlueprintCallable)
		float GetAspectRatioHeight();


    UFUNCTION(BlueprintCallable)
        void MoveCamera(int screenCount);
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
        void ToStop();
    UFUNCTION(BlueprintCallable)
        void ToCancel();
    UFUNCTION(BlueprintCallable)
        bool MakeDataset();
};
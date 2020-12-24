// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCamera.h"

// Sets default values
AMyCamera::AMyCamera()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	PPSettings.DepthOfFieldFocalDistance = 500.0f;
	PPSettings.CameraISO = 100.0f;
	PPSettings.DepthOfFieldFstop = 4.0f;
	PPSettings.DepthOfFieldMinFstop = 4.0f;
	PPSettings.WhiteTemp = 6500.0f;
	PPSettings.WhiteTint = 0.0f;

	camera->PostProcessSettings = PPSettings;
	camera->AspectRatio = aspectRatioImage.GetAspectRatio();
	

    RootComponent = mesh;
    meshVector = startPositionMesh;

    springArm->AttachTo(RootComponent);
    springArm->TargetArmLength = 500.f;
    springArm->SetWorldRotation(FRotator(0.f, 0.f, 0.f));

    camera->AttachTo(springArm, USpringArmComponent::SocketName);

    AutoPossessPlayer = EAutoReceiveInput::Player0;

    deltaOfAngle = 0;
    fullAngle = 0;
    screenCount = 0;
}

// Called when the game starts or when spawned
void AMyCamera::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void AMyCamera::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    mesh->SetWorldLocation(meshVector);

    if (playIt == false)
    {
        FRotator newYaw = GetActorRotation();
        newYaw.Yaw = angleInput.X;
        endPos.Yaw = angleInput.X;
        SetActorRotation(newYaw);

        /*
		FRotator newRoll = springArm->GetComponentRotation();
        newRoll.Roll = FMath::Clamp(angleInput.Z, -180.f, 180.f);
        endPos.Roll = angleInput.Z;
        springArm->SetWorldRotation(newRoll);
        */
        FRotator newRoll = GetActorRotation();
        newRoll.Roll = angleInput.Z;
        endPos.Roll = angleInput.Z;
        SetActorRotation(newRoll);

        /*
		FRotator newPitch = GetActorRotation();
        newPitch.Pitch = angleInput.Y;
        endPos.Pitch = angleInput.Y;
        SetActorRotation(newPitch);
        */
        FRotator newPitch = GetActorRotation();
        //newPitch.Pitch = FMath::Clamp(angleInput.Y, -180.f, 0.f);
        newPitch.Pitch = angleInput.Y;
        endPos.Pitch = angleInput.Y;
        SetActorRotation(newPitch);
        //springArm->SetWorldRotation(newPitch);
        deltaOfAngle = 0;
    }
    else if (playIt == true)
    {
        if (rightIt) {
            screenCount = 4;
            if (++deltaOfAngle >= fullAngle / screenCount)//пора делать скриншот
            {
                deltaOfAngle = 0;
            }
            angleInput.X -= 1.0f;
            FRotator newYawM = GetActorRotation();
            newYawM.Yaw = angleInput.X;
            SetActorRotation(newYawM);
            if (angleInput.X == (endPos.Yaw - 360.f))
            {
                ToCancel();
                StopMoveCamera();
            }
        }
        else if (leftIt) {
            screenCount = 4;
            if (++deltaOfAngle >= fullAngle / screenCount)//пора делать скриншот
            {
                deltaOfAngle = 0;
            }
            angleInput.X += 1.0f;
            FRotator newYawM = GetActorRotation();
            newYawM.Yaw = angleInput.X;
            SetActorRotation(newYawM);
            if (angleInput.X == (endPos.Yaw + 360.f))
            {
                ToCancel();
                StopMoveCamera();
            }
        }
        else if (upIt) {
			/* ПЛОХО РАБОТАЕТ ИЗ-ЗА ОСОБЕННОСТЕЙ ДВИЖКА
            if (angleInput.Y == ((-1.0f) * endPos.Pitch - 180.0f))
            {
                angleInput.X = endPos.Yaw + 180.0f;
                angleInput.Y = endPos.Pitch;
                ToCancel();
                StopMoveCamera();
            }
            else if ((angleInput.Y > -90.0f) && (angleInput.Y <= endPos.Pitch))
            {
                angleInput.Y -= 1.0f;
                FRotator newPitchM = GetActorRotation();
                newPitchM.Pitch = angleInput.Y;
                SetActorRotation(newPitchM);
                //FRotator newPitch = springArm->GetComponentRotation();
            }
            else if ((angleInput.Y <= -90.0f) && (angleInput.Y > (((-1) * endPos.Pitch) - 180.0f)))
            {
                angleInput.Y -= 1.0f;
                FRotator newPitchM2 = GetActorRotation();
                newPitchM2.Pitch = angleInput.Y;
                newPitchM2.Roll = angleInput.Z + 180.0f;
                SetActorRotation(newPitchM2);
            }
            //newPitchM.Pitch = FMath::Clamp(angleInput.Y, -180.f, 0.f);
            //springArm->SetWorldRotation(newPitch);
			*/
            screenCount = 4;
            if (++deltaOfAngle >= fullAngle / screenCount)//пора делать скриншот
            {
                deltaOfAngle = 0;
            }
			FRotator newPitchM = GetActorRotation();
			if (flagForUpDown == false)
			{
				angleInput.Y -= 1.0f;
				if (angleInput.Y ==  (-89.0f))
				{
					flagForUpDown = true;
					angleInput.X += 180.0f;
					newPitchM.Yaw = angleInput.X;
				}
			}
			else if (flagForUpDown == true)
			{
				angleInput.Y += 1.0f;
			}
			newPitchM.Yaw = angleInput.X;
			newPitchM.Pitch = angleInput.Y;
			SetActorRotation(newPitchM);

			if (angleInput.Y == endPos.Pitch) flagForFinishMove = true;

			if (flagForFinishMove == true)
			{
				flagForUpDown = false;
				flagForFinishMove = false;
				ToCancel();
				StopMoveCamera();
			}

        }
        else if (downIt) {
			/* ПЛОХО РАБОТАЕТ ИЗ-ЗА ОСОБЕННОСТЕЙ ДВИЖКА
			if (angleInput.Y == (endPos.Pitch + 180.0f))
			{
				angleInput.X = endPos.Yaw + 180.0f;
				angleInput.Z -= 180.0f;
				angleInput.Y = endPos.Pitch;
				flagForRoll = false;
				ToCancel();
				StopMoveCamera();
			}
			else if ((angleInput.Y < 90.0f) && (angleInput.Y >= endPos.Pitch))
			{
				angleInput.Y += 1.0f;
				FRotator newPitchM = GetActorRotation();
				newPitchM.Pitch = angleInput.Y;
				SetActorRotation(newPitchM);
				//FRotator newPitch = springArm->GetComponentRotation();
			}
			else if ((angleInput.Y >= 90.0f) && (angleInput.Y < (endPos.Pitch + 180.0f)))
			{
				if (flagForRoll == false)
				{
					flagForRoll = true;
					angleInput.Z += 180.0f;
				}
				angleInput.Y += 1.0f;
				FRotator newPitchM2 = GetActorRotation();
				newPitchM2.Pitch = angleInput.Y;
				newPitchM2.Roll = angleInput.Z;
				SetActorRotation(newPitchM2);
			}
			*/
            screenCount = 4;
            if (++deltaOfAngle >= fullAngle / screenCount)//пора делать скриншот
            {
                deltaOfAngle = 0;
            }

			FRotator newPitchM = GetActorRotation();
			if (flagForUpDown == false)
			{
				angleInput.Y += 1.0f;
				if (angleInput.Y == (89.0f))
				{
					flagForUpDown = true;
					angleInput.X += 180.0f;
					newPitchM.Yaw = angleInput.X;
				}
			}
			else if (flagForUpDown == true)
			{
				angleInput.Y -= 1.0f;
			}
			newPitchM.Yaw = angleInput.X;
			newPitchM.Pitch = angleInput.Y;
			SetActorRotation(newPitchM);

			if (angleInput.Y == endPos.Pitch) flagForFinishMove = true;

			if (flagForFinishMove == true)
			{
				flagForUpDown = false;
				flagForFinishMove = false;
				ToCancel();
				StopMoveCamera();
			}

        }
        else if (urIt) {

            screenCount = 4;
            if (++deltaOfAngle >= fullAngle / screenCount)//пора делать скриншот
            {
                deltaOfAngle = 0;
            }

			angleInput.X -= 1.0f;
			FRotator newAngleActor = GetActorRotation();

			if (flagForUpDown == false)
			{
				angleInput.Y -= 0.5f;
				if(angleInput.Y == endPos.Pitch - 45.0f) flagForUpDown = true;
			}
			else if (flagForUpDown == true)
			{
				angleInput.Y += 0.5f;
			}
			newAngleActor.Yaw = angleInput.X;
			newAngleActor.Pitch = angleInput.Y;
			SetActorRotation(newAngleActor);

			if (angleInput.X == (endPos.Yaw - 180.0f))
			{
				flagForUpDown = false;
				ToCancel();
				StopMoveCamera();
			}

		}
        else if (ulIt) {

            screenCount = 4;
            if (++deltaOfAngle >= fullAngle / screenCount)//пора делать скриншот
            {
                deltaOfAngle = 0;
            }

			angleInput.X += 1.0f;
			FRotator newAngleActor = GetActorRotation();
	
			if (flagForUpDown == false)
			{
				angleInput.Y -= 0.5f;
				if (angleInput.Y == endPos.Pitch - 45.0f) flagForUpDown = true;
			}
			else if (flagForUpDown == true)
			{
				angleInput.Y += 0.5f;
			}
			newAngleActor.Yaw = angleInput.X;
			newAngleActor.Pitch = angleInput.Y;
			SetActorRotation(newAngleActor);

			if (angleInput.X == (endPos.Yaw + 180.0f))
			{
				flagForUpDown = false;
				ToCancel();
				StopMoveCamera();
			}
        }
        else if (drIt) {

            screenCount = 4;
            if (++deltaOfAngle >= fullAngle / screenCount)//пора делать скриншот
            {
                deltaOfAngle = 0;
            }

			angleInput.X -= 1.0f;
			FRotator newAngleActor = GetActorRotation();

			if (flagForUpDown == false)
			{
				angleInput.Y += 0.5f;
				if (angleInput.Y == endPos.Pitch + 45.0f) flagForUpDown = true;
			}
			else if (flagForUpDown == true)
			{
				angleInput.Y -= 0.5f;
			}
			newAngleActor.Yaw = angleInput.X;
			newAngleActor.Pitch = angleInput.Y;
			SetActorRotation(newAngleActor);

			if (angleInput.X == (endPos.Yaw - 180.0f))
			{
				flagForUpDown = false;
				ToCancel();
				StopMoveCamera();
			}
        }
        else if (dlIt) {

            screenCount = 4;
            if (++deltaOfAngle >= fullAngle / screenCount)//пора делать скриншот
            {
                deltaOfAngle = 0;
            }

			angleInput.X += 1.0f;
			FRotator newAngleActor = GetActorRotation();

			if (flagForUpDown == false)
			{
				angleInput.Y += 0.5f;
				if (angleInput.Y == endPos.Pitch + 45.0f) flagForUpDown = true;
			}
			else if (flagForUpDown == true)
			{
				angleInput.Y -= 0.5f;
			}
			newAngleActor.Yaw = angleInput.X;
			newAngleActor.Pitch = angleInput.Y;
			SetActorRotation(newAngleActor);

			if (angleInput.X == (endPos.Yaw + 180.0f))
			{
				flagForUpDown = false;
				ToCancel();
				StopMoveCamera();
			}
        }
        else if (stopIt) {
            //angleInput = { 0.f , 0.f , 0.f };
            //newAngleActor = angleInput;
            //SetActorRotation(angleInput);
            //ToCancel();
            //StopMoveCamera();
            FRotator newAngleActor = GetActorRotation();
            newAngleActor = { 0.0f, 0.0f, 0.0f };
            angleInput = { 0.0f, 0.0f, 0.0f };
            SetActorRotation(newAngleActor);
            ToCancel();
            StopMoveCamera();
        }

    }

    springArm->TargetArmLength = FMath::FInterpTo(springArm->TargetArmLength, DesiredArmLength, DeltaTime, 5.0f);
}

bool AMyCamera::MakeDataset()
{
   //вычисление делать скриншот или нет
    if (!deltaOfAngle && playIt && fullAngle)
        return true;

    return false;

}

// Called to bind functionality to input
void AMyCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}


void AMyCamera::SetCameraYaw(float axis)
{
    angleInput.X = axis;
}

void AMyCamera::SetCameraPitch(float axis)
{
    if(axis > -90.0f && axis < 90.0f) angleInput.Y = axis * (-1);
    else if (axis > 90.0f) angleInput.Y = 89.0f;
    else if (axis < -90.0f) angleInput.Y = -89.0f;
    //angleInput.Y = axis * (-1.0f);
}
void AMyCamera::SetCameraRoll(float axis)
{
    angleInput.Z = axis;
}

void AMyCamera::SetArmLenght(float axis)
{
    DesiredArmLength = axis;
}

void AMyCamera::SetMeshVectorX(float axis)
{
    meshVector.X = axis;
}

void AMyCamera::SetMeshVectorY(float axis)
{
    meshVector.Y = axis;
}

void AMyCamera::SetMeshVectorZ(float axis)
{
        meshVector.Z = axis;
}

void AMyCamera::SetFocalDistance(float axis)
{
	PPSettings.DepthOfFieldFocalDistance = axis;
	camera->PostProcessSettings.DepthOfFieldFocalDistance = axis;
}

void AMyCamera::SetISO(float axis)
{
	PPSettings.CameraISO = axis;
	camera->PostProcessSettings.CameraISO = axis;
}

void AMyCamera::SetFStop(float axis) {
	PPSettings.DepthOfFieldFstop = axis;
	camera->PostProcessSettings.DepthOfFieldFstop = axis;
}

void AMyCamera::SetMFStop(float axis) {
	PPSettings.DepthOfFieldMinFstop = axis;
	camera->PostProcessSettings.DepthOfFieldMinFstop = axis;
}

void AMyCamera::SetWhiteTemp(float axis) {
	PPSettings.WhiteTemp = axis;
	camera->PostProcessSettings.WhiteTemp = axis;
}

void AMyCamera::SetWhiteTint(float axis) {
	PPSettings.WhiteTint = axis;
	camera->PostProcessSettings.WhiteTint = axis;
}
void AMyCamera::SetAspectRatioWidth(float axis) {
	aspectRatioImage.SetWidth(axis);
	aspectRatioImage.SetAspectRatio();
}
void AMyCamera::SetAspectRatioHeight(float axis) {
	aspectRatioImage.SetHeight(axis);
	aspectRatioImage.SetAspectRatio();
}

void AMyCamera::SetAspectRatio() {
	aspectRatioImage.SetAspectRatio();
	camera->AspectRatio = aspectRatioImage.GetAspectRatio();
}



float AMyCamera::GetViewAngleX()
{
    return angleInput.X;
}

float AMyCamera::GetViewAngleY()
{
    return (-1) * angleInput.Y;
}

float AMyCamera::GetViewAngleZ()
{
    return angleInput.Z;
}

float AMyCamera::GetMeshCoordX()
{
    return meshVector.X;
}

float AMyCamera::GetMeshCoordY()
{
    return meshVector.Y;
}

float AMyCamera::GetMeshCoordZ()
{
    return meshVector.Z;
}

float AMyCamera::GetArmLenght()
{
	return DesiredArmLength;
}

float AMyCamera::GetFocalDistance()
{
	return PPSettings.DepthOfFieldFocalDistance;
}

float AMyCamera::GetISO()
{
	return PPSettings.CameraISO;
}

float AMyCamera::GetFStop() {
	return PPSettings.DepthOfFieldFstop;
}

float AMyCamera::GetMFStop() {
	return PPSettings.DepthOfFieldMinFstop;
}

float AMyCamera::GetWhiteTemp() {
	return PPSettings.WhiteTemp;
}

float AMyCamera::GetWhiteTint() {
	return PPSettings.WhiteTint;
}
float AMyCamera::GetAspectRatioWidth() {
	return aspectRatioImage.GetWidth();
}
float AMyCamera::GetAspectRatioHeight() {
	return aspectRatioImage.GetHeight();
}


void AMyCamera::MoveCamera(int count)
{
    //if (screenCount)
    {
        screenCount = 1.0f * count;
        playIt = true;

    }

}

void AMyCamera::StopMoveCamera()
{
    playIt = false;
}

void AMyCamera::ToRight()
{
    rightIt = true;
    upIt = false;
    downIt = false;
    leftIt = false;
    ulIt = false;
    urIt = false;
    dlIt = false;
    drIt = false;
    stopIt = false;

    fullAngle = 360;
}

void AMyCamera::ToLeft()
{
    leftIt = true;
    rightIt = false;
    upIt = false;
    downIt = false;
    ulIt = false;
    urIt = false;
    dlIt = false;
    drIt = false;
    stopIt = false;

    fullAngle = 360;
}

void AMyCamera::ToUp()
{
    upIt = true;
    rightIt = false;
    downIt = false;
    leftIt = false;
    ulIt = false;
    urIt = false;
    dlIt = false;
    drIt = false;
    stopIt = false;

    fullAngle = 178;
}

void AMyCamera::ToDown()
{
    downIt = true;
    rightIt = false;
    upIt = false;
    leftIt = false;
    ulIt = false;
    urIt = false;
    dlIt = false;
    drIt = false;
    stopIt = false;

    fullAngle = 178;
}

void AMyCamera::ToUR()
{
    urIt = true;
    downIt = false;
    rightIt = false;
    upIt = false;
    leftIt = false;
    ulIt = false;
    dlIt = false;
    drIt = false;
    stopIt = false;

    fullAngle = 180;
}

void AMyCamera::ToUL()
{
    ulIt = true;
    downIt = false;
    rightIt = false;
    upIt = false;
    leftIt = false;
    urIt = false;
    dlIt = false;
    drIt = false;
    stopIt = false;

    fullAngle = 180;
}

void AMyCamera::ToDL()
{
    dlIt = true;
    downIt = false;
    rightIt = false;
    upIt = false;
    leftIt = false;
    ulIt = false;
    urIt = false;
    drIt = false;
    stopIt = false;

    fullAngle = 180;
}

void AMyCamera::ToDR()
{
    drIt = true;
    downIt = false;
    rightIt = false;
    upIt = false;
    leftIt = false;
    ulIt = false;
    urIt = false;
    dlIt = false;
    stopIt = false;

    fullAngle = 180;
}
void AMyCamera::ToStop()
{
    stopIt = true;
    downIt = false;
    rightIt = false;
    upIt = false;
    leftIt = false;
    ulIt = false;
    urIt = false;
    dlIt = false;
    drIt = false;
}

void AMyCamera::ToCancel()
{
    stopIt = false;
    downIt = false;
    rightIt = false;
    upIt = false;
    leftIt = false;
    ulIt = false;
    urIt = false;
    dlIt = false;
    drIt = false;
}
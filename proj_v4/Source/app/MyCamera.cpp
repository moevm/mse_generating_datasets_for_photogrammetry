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

        /*FRotator newRoll = springArm->GetComponentRotation();
        newRoll.Roll = FMath::Clamp(angleInput.Z, -180.f, 180.f);
        endPos.Roll = angleInput.Z;
        springArm->SetWorldRotation(newRoll);
        */
        FRotator newRoll = GetActorRotation();
        newRoll.Roll = angleInput.Z;
        endPos.Roll = angleInput.Z;
        SetActorRotation(newRoll);

        /*FRotator newPitch = GetActorRotation();
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
                FRotator newPitchM = GetActorRotation();
                newPitchM.Pitch = angleInput.Y;
                newPitchM.Roll = 180.0f;
                SetActorRotation(newPitchM);
            }
            //newPitchM.Pitch = FMath::Clamp(angleInput.Y, -180.f, 0.f);
            //springArm->SetWorldRotation(newPitch);


        }
        else if (downIt) {
            angleInput.Y += 1.0f;
            if (angleInput.Y == (endPos.Pitch + 180.0f))
            {
                angleInput.X = endPos.Yaw + 180.0f;
                angleInput.Y = endPos.Pitch;

                ToCancel();
                StopMoveCamera();
            }
            if ((angleInput.Y > 90.0f) && (angleInput.Y <= endPos.Pitch)) {
                FRotator newPitchM = GetActorRotation();
                newPitchM.Pitch = angleInput.Y;
                SetActorRotation(newPitchM);
                //FRotator newPitch = springArm->GetComponentRotation();
            }
            else if ((angleInput.Y < 90.0f) && (angleInput.Y > endPos.Pitch + 180))
            {
                FRotator newPitchM = GetActorRotation();
                newPitchM.Pitch = angleInput.Y;
                newPitchM.Roll = 180.0f;
                SetActorRotation(newPitchM);
            }
            //newPitchM.Pitch = FMath::Clamp(angleInput.Y, -180.f, 0.f);
            //springArm->SetWorldRotation(newPitch);

        }
        else if (urIt) {
        }
        else if (ulIt) {
        }
        else if (drIt) {
        }
        else if (dlIt) {
        }
        else if (randIt) {
        }

    }

    springArm->TargetArmLength = FMath::FInterpTo(springArm->TargetArmLength, DesiredArmLength, DeltaTime, 5.0f);
}

bool AMyCamera::MakeDataset()
{
    // FViewport->TakeHighResScreenshot();
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
    angleInput.Y = axis * (-1.0f);
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
    if (axis >= 50.f)
        meshVector.Z = axis;
    else
        axis = 50.f;
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
    randIt = false;

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
    randIt = false;

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
    randIt = false;

    fullAngle = 180;
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
    randIt = false;

    fullAngle = 180;
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
    randIt = false;
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
    randIt = false;
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
    randIt = false;
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
    randIt = false;
}
void AMyCamera::ToRand()
{
    randIt = true;
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
    randIt = false;
    downIt = false;
    rightIt = false;
    upIt = false;
    leftIt = false;
    ulIt = false;
    urIt = false;
    dlIt = false;
    drIt = false;
}
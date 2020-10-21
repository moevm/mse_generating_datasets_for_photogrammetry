#include "MyPawn.h"

// Sets default values
AMyPawn::AMyPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	RootComponent = mesh;

	FVector startPositionMesh = {0.0f, 0.0f, 50.0f};
	meshVector = startPositionMesh;

	springArm->AttachTo(RootComponent);
	springArm->TargetArmLength = 500.f;
	springArm->SetWorldRotation(FRotator(0.f, 0.f, 0.f));

	camera->AttachTo(springArm, USpringArmComponent::SocketName);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	mesh->SetWorldLocation(meshVector);

	FRotator newYaw = GetActorRotation();
	newYaw.Yaw = angleInput.X;
	SetActorRotation(newYaw);

	FRotator newPitch = springArm->GetComponentRotation();
	newPitch.Pitch = FMath::Clamp(angleInput.Y, -90.f, 0.f);
	springArm->SetWorldRotation(newPitch);

	springArm->TargetArmLength = FMath::FInterpTo(springArm->TargetArmLength, DesiredArmLength, DeltaTime, 5.0f);
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMyPawn::SetCameraYaw(float axis) 
{
	angleInput.X = axis;
}

void AMyPawn::SetCameraPitch(float axis) 
{
	angleInput.Y = axis * (-1);
}

void AMyPawn::SetArmLenght(float axis)
{
	DesiredArmLength = axis;
}

void AMyPawn::SetMeshVectorX(float axis)
{
	meshVector.X = axis;
}

void AMyPawn::SetMeshVectorY(float axis)
{
	meshVector.Y = axis;
}


void AMyPawn::SetMeshVectorZ(float axis)
{
	meshVector.Z = axis;
}

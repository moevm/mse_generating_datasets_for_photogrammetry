// Fill out your copyright notice in the Description page of Project Settings.
#include "MyActor.h"
#include "Engine/StaticMesh.h"
#include "UObject/UObjectGlobals.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyActor::DoSomething() {
	
	//UStaticMeshComponent* MeshComponent;
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshToUse(TEXT("C:/Users/yakru/Documents/Unreal Projects/proj_v4/Content/Meshes/Viewer/SM_Dummy.uasset");

	//MeshComponent->SetStaticMesh(MeshToUse.Object);
	UStaticMesh* mt = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/Meshes/SM_Dummy"));
	UE_LOG(LogTemp, Warning, TEXT("DoSomething()"));

}


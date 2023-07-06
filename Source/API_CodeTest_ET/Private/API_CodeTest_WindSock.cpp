// Fill out your copyright notice in the Description page of Project Settings.


#include "API_CodeTest_WindSock.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AAPI_CodeTest_WindSock::AAPI_CodeTest_WindSock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(Body);
}

// Called when the game starts or when spawned
void AAPI_CodeTest_WindSock::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAPI_CodeTest_WindSock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


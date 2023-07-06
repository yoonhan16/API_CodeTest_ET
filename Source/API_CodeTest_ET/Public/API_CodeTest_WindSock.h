// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "API_CodeTest_WindSock.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class API_CODETEST_ET_API AAPI_CodeTest_WindSock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAPI_CodeTest_WindSock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UBoxComponent* Box;

	UStaticMeshComponent* Body;
};

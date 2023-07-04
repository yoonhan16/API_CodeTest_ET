// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "API_CodeTest_Instance.generated.h"

/**
 * 
 */
UCLASS()
class API_CODETEST_ET_API UAPI_CodeTest_Instance : public UGameInstance
{
	GENERATED_BODY()

public:

    UFUNCTION(BlueprintCallable)
    void StartTCPServer(const FString& ServerIP, const int32 ServerPort, const FString& JSONData);

    UFUNCTION(BlueprintCallable)
    void GetOpenAPIJSONData(const FString& EncodingKey, const FString& DecodingKey, const FString& ServerIP, const int32 ServerPort);

};

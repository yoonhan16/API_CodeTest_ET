// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "HttpModule.h"
#include "Json.h"
#include "JsonUtilities.h"
#include "API_CodeTest_Instance.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FWeatherData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
        FString baseDate;

    UPROPERTY(BlueprintReadOnly)
        FString baseTime;

    UPROPERTY(BlueprintReadOnly)
        FString category;

    UPROPERTY(BlueprintReadOnly)
        FString fcstDate;

    UPROPERTY(BlueprintReadOnly)
        FString fcstTime;

    UPROPERTY(BlueprintReadOnly)
        FString fcstValue;

    UPROPERTY(BlueprintReadOnly)
        int32 nx;

    UPROPERTY(BlueprintReadOnly)
        int32 ny;
};

UCLASS()
class API_CODETEST_ET_API UAPI_CodeTest_Instance : public UGameInstance
{
	GENERATED_BODY()

public:

    UAPI_CodeTest_Instance();

    UFUNCTION(BlueprintCallable)
    void FetchWeatherData();

private:
    void OnWeatherDataReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
    void ParseWeatherData(const FString& JsonString, TArray<FWeatherData>& WeatherDataArray);

};

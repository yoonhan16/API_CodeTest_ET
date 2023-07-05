// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "API_CodeTest_Instance.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WeatherDataLibrary.generated.h"

/**
 * 
 */
UCLASS()
class API_CODETEST_ET_API UWeatherDataLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "WeatherData")
	static FString WeatherDataToString(const FWeatherData& WeatherData);

};

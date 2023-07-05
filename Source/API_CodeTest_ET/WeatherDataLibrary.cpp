
// Fill out your copyright notice in the Description page of Project Settings.


#include "WeatherDataLibrary.h"

FString UWeatherDataLibrary::WeatherDataToString(const FWeatherData& WeatherData)
{
    return FString::Printf(TEXT("BaseDate: %s, BaseTime: %s, Category: %s, FcstDate: %s, FcstTime: %s, FcstValue: %s, nx: %d, ny: %d"),
        *WeatherData.baseDate, *WeatherData.baseTime, *WeatherData.category, *WeatherData.fcstDate, *WeatherData.fcstTime,
        *WeatherData.fcstValue, WeatherData.nx, WeatherData.ny);
}

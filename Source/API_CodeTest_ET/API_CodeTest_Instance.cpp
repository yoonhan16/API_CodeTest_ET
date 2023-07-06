// Fill out your copyright notice in the Description page of Project Settings.


#include "API_CodeTest_Instance.h"
#include "HttpModule.h"
#include "Json.h"
#include "JsonUtilities.h"
#include "Interfaces/IHttpResponse.h"
#include "WeatherDataLibrary.h"



UAPI_CodeTest_Instance::UAPI_CodeTest_Instance()
{
    FetchWeatherData();
}

void UAPI_CodeTest_Instance::FetchWeatherData()
{
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
    HttpRequest->SetVerb("GET");
    HttpRequest->SetURL("http://127.0.0.1:3000/weather");

    // Request completion callback
    HttpRequest->OnProcessRequestComplete().BindUObject(this, &UAPI_CodeTest_Instance::OnWeatherDataReceived);

    HttpRequest->ProcessRequest();
}

void UAPI_CodeTest_Instance::OnWeatherDataReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (bWasSuccessful && Response.IsValid())
    {
        FString ResponseStr = Response->GetContentAsString();

        TArray<FWeatherData> WeatherDataArray;
        ParseWeatherData(ResponseStr, WeatherDataArray);
    }
}

void UAPI_CodeTest_Instance::ParseWeatherData(const FString& JsonString, TArray<FWeatherData>& WeatherDataArray)
{
    // Deserialize JSON string to JSON object
    TSharedPtr<FJsonObject> JsonObject;
    TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);
    if (!FJsonSerializer::Deserialize(JsonReader, JsonObject) || !JsonObject.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to parse JSON string."));
        return;
    }

    // Get "message" object
    const TSharedPtr<FJsonObject>* MessageObject;
    if (!JsonObject->TryGetObjectField("message", MessageObject))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to get \"message\" object from JSON object."));
        return;
    }

    // Get "item" array from "message" object
    const TArray<TSharedPtr<FJsonValue>>* ItemArray;
    if (!(*MessageObject)->TryGetArrayField("item", ItemArray))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to get \"item\" array from \"message\" object."));
        return;
    }

    // Clear the output array
    WeatherDataArray.Empty();

    // Iterate through each item in the array
    for (const TSharedPtr<FJsonValue>& ItemValue : *ItemArray)
    {
        const TSharedPtr<FJsonObject>& ItemObject = ItemValue->AsObject();
        if (ItemObject.IsValid())
        {
            // Create a new FWeatherData object
            FWeatherData WeatherData;

            // Retrieve values from the JSON object and assign them to the FWeatherData object
            WeatherData.baseDate = ItemObject->GetStringField("baseDate");
            WeatherData.baseTime = ItemObject->GetStringField("baseTime");
            WeatherData.category = ItemObject->GetStringField("category");
            WeatherData.fcstDate = ItemObject->GetStringField("fcstDate");
            WeatherData.fcstTime = ItemObject->GetStringField("fcstTime");
            WeatherData.fcstValue = ItemObject->GetStringField("fcstValue");
            WeatherData.nx = ItemObject->GetIntegerField("nx");
            WeatherData.ny = ItemObject->GetIntegerField("ny");

            // Add the FWeatherData object to the output array
            WeatherDataArray.Add(WeatherData);
            UE_LOG(LogTemp, Warning, TEXT("JSON Data added to WeatherDataArray."));
        }
    }
}


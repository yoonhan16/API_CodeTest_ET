// Fill out your copyright notice in the Description page of Project Settings.


#include "API_CodeTest_Instance.h"
#include "HttpModule.h"
#include "Json.h"
#include "JsonUtilities.h"
#include "Interfaces/IHttpResponse.h"

void UAPI_CodeTest_Instance::API_CodeTest_Instance()
{
}

void UAPI_CodeTest_Instance::FetchWeatherData()
{
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
    HttpRequest->SetVerb("GET");
    HttpRequest->SetURL("http://127.0.0.1:3000/weather");

    // 요청 완료 시 호출될 콜백 함수 설정
    HttpRequest->OnProcessRequestComplete().BindUObject(this, &UAPI_CodeTest_Instance::OnWeatherDataReceived);

    HttpRequest->ProcessRequest();
}

void UAPI_CodeTest_Instance::OnWeatherDataReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (bWasSuccessful && Response.IsValid())
    {
        FString ResponseStr = Response->GetContentAsString();

        TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
        TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(ResponseStr);

        if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
        {
            FWeatherData WeatherData;
            FJsonObjectConverter::JsonObjectToUStruct<FWeatherData>(JsonObject.ToSharedRef(), &WeatherData);
        }
    }
}


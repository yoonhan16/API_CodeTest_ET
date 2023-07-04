// Fill out your copyright notice in the Description page of Project Settings.


#include "API_CodeTest_Instance.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "IPAddress.h"
#include "HttpModule.h"
#include "Json.h"
#include <Interfaces/IPv4/IPv4Address.h>
#include <Common/TcpSocketBuilder.h>


void UAPI_CodeTest_Instance::StartTCPServer(const FString& ServerIP, const int32 ServerPort, const FString& JSONData)
{
    FIPv4Address IPAddress;
    FIPv4Address::Parse(ServerIP, IPAddress);

    TSharedRef<FInternetAddr> ServerAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
    ServerAddr->SetIp(IPAddress.Value);
    ServerAddr->SetPort(ServerPort);

    FString SocketName = "MyTCPServerSocket";

    // TCP 소켓 생성
    FSocket* ListenSocket = FTcpSocketBuilder(SocketName)
        .AsReusable()
        .WithSendBufferSize(2 * 1024 * 1024)
        .WithReceiveBufferSize(2 * 1024 * 1024)
        .BoundToAddress(ServerAddr)
        .Listening(8)
        .Build();

    if (ListenSocket)
    {
        UE_LOG(LogTemp, Log, TEXT("Server listening on: %s:%d"), *ServerIP, ServerPort);

        // 클라이언트 접속 대기
        bool bPending = false;
        while (true)
        {
            // 클라이언트 소켓 생성 및 연결 수락
            FSocket* ClientSocket = ListenSocket->Accept(TEXT("ClientSocket"), bPending);
            if (ClientSocket)
            {
                UE_LOG(LogTemp, Log, TEXT("Client connected: %s"), *ClientSocket->GetDescription());

                // 클라이언트에 JSON 데이터 전송
                int32 SentBytes = 0;
                bool Success = ClientSocket->Send((uint8*)TCHAR_TO_UTF8(*JSONData), JSONData.Len(), SentBytes);
                if (Success)
                {
                    UE_LOG(LogTemp, Log, TEXT("JSON data sent to client: %s"), *JSONData);
                }
                else
                {
                    UE_LOG(LogTemp, Error, TEXT("Failed to send JSON data to client."));
                }

                // 클라이언트 연결 종료
                ClientSocket->Close();
            }

            if (!bPending)
            {
                // 더 이상 대기 중인 클라이언트가 없으면 종료
                break;
            }
        }

        // 소켓 종료
        ListenSocket->Close();
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create server socket."));
    }
}

void UAPI_CodeTest_Instance::GetOpenAPIJSONData(const FString& EncodingKey, const FString& DecodingKey, const FString& ServerIP, const int32 ServerPort)
{
    // Open API 요청
    FString OpenAPIURL = TEXT("http://apis.data.go.kr/1360000/VilageFcstMsgService"); // Open API URL
    FString RequestURL = OpenAPIURL + "?encodingKey=" + EncodingKey; // 요청 URL

    // HTTP 요청 생성
    TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
    HttpRequest->SetVerb("GET");
    HttpRequest->SetURL(RequestURL);

    // HTTP 요청 완료 시 콜백 함수 설정
    HttpRequest->OnProcessRequestComplete().BindUObject(this, &UAPI_CodeTest_Instance::OnHttpRequestComplete, ServerIP, ServerPort);

    // HTTP 요청 보내기
    HttpRequest->ProcessRequest();
}

void UAPI_CodeTest_Instance::OnHttpRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess, const FString& ServerIP, const int32 ServerPort)
{
    if (bSuccess && Response.IsValid())
    {
        int32 ResponseCode = Response->GetResponseCode();
        if (ResponseCode == 200)
        {
            FString ResponseContent = Response->GetContentAsString();
            UE_LOG(LogTemp, Log, TEXT("Received JSON data from Open API: %s"), *ResponseContent);

            // 서버에 JSON 데이터 전송
            StartTCPServer(ServerIP, ServerPort, ResponseContent);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("HTTP request failed with response code: %d"), ResponseCode);
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("HTTP request failed."));
    }
}
// Fill out your copyright notice in the Description page of Project Settings.

#include "ServerWebSocketSubsystem.h"

#include "ServerWebSocketModule.h"
#include "IServerWebSocket.h"
#include "INetWebSocket.h"
#include "ServerWebSocketDelegates.h"
#include "ServerWebSocketPrivate.h"


bool UServerWebSocketSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return bUseSubsystem;
}

void UServerWebSocketSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	ServerWebSocket = FServerWebSocketModule::Get().CreateServer();

	FNetWebSocketClientConnectedCallBack CallBack;
	CallBack.BindUObject(this, &UServerWebSocketSubsystem::OnWebSocketClientConnected);

	if (!ServerWebSocket->Init(WebSocketPort, CallBack))
	{
		UE_LOG(LogServerWebSocket, Warning, TEXT("ServerWebSocket Init FAIL"));
		ServerWebSocket.Reset();
		CallBack.Unbind();
		return;
	}

	TickHandle = FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateLambda([=](float Time)		
	{
		if (ServerWebSocket)
		{
			ServerWebSocket->Tick();
			return true;
		}
		else
		{
			return false;
		}
	}));
}

void UServerWebSocketSubsystem::Deinitialize()
{
	ServerWebSocket = nullptr;

	if (TickHandle.IsValid())
	{
		FTSTicker::GetCoreTicker().RemoveTicker(TickHandle);
		TickHandle.Reset();
	}
}

void UServerWebSocketSubsystem::OnWebSocketClientConnected(INetWebSocket* ClientWebSocket)
{
	FNetWebSocketPacketReceivedCallBack CallBack;
	CallBack.BindUObject(this, &UServerWebSocketSubsystem::ReceivedRawPacket);

	ClientWebSocket->SetReceiveCallBack(CallBack);
}

void UServerWebSocketSubsystem::ReceivedRawPacket(void* Data, int32 Count)
{
	if (Count == 0)   // nothing to process
	{
		return;
	}

	const uint8* DataRef = reinterpret_cast<uint8*>(Data);

	const TArray<uint8> MessageData(DataRef, Count);

	const FString JSonData = UTF8_TO_TCHAR(MessageData.GetData());

	OnJsonRecieved.Broadcast(JSonData);
}

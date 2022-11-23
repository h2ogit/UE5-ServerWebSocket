// Copyright Epic Games, Inc. All Rights Reserved.

#include "ServerWebSocketModule.h"
#include "ServerWebSocketPrivate.h"
#include "ServerWebSocket.h"
#include "NetWebSocket.h"


DEFINE_LOG_CATEGORY(LogServerWebSocket);

IMPLEMENT_MODULE(FServerWebSocketModule, ServerWebSocketModule)

FServerWebSocketModule* FServerWebSocketModule::Singleton = nullptr;


void FServerWebSocketModule::StartupModule()
{
	Singleton = this;
}

void FServerWebSocketModule::ShutdownModule()
{
	Singleton = nullptr;
}

FServerWebSocketModule& FServerWebSocketModule::Get()
{
	return *Singleton;
}

TUniquePtr<IServerWebSocket> FServerWebSocketModule::CreateServer()
{
	return MakeUnique<FServerWebSocket>();
}
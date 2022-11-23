// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class INetWebSocket;

DECLARE_DELEGATE(FNetWebSocketInfoCallBack);
DECLARE_DELEGATE_TwoParams(FNetWebSocketPacketReceivedCallBack, void* /*Data*/, int32 /*Data Size*/);
DECLARE_DELEGATE_OneParam(FNetWebSocketClientConnectedCallBack, INetWebSocket* /*Socket*/);
						  

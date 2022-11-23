// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreFwd.h"
#include "ServerWebSocketDelegates.h"

class SERVERWEBSOCKET_API INetWebSocket
{
public:
	virtual ~INetWebSocket() {}

	/************************************************************************/
	/* Set various callbacks for Socket Events                              */
	/************************************************************************/
	virtual void SetConnectedCallBack(FNetWebSocketInfoCallBack CallBack) = 0;
	virtual void SetErrorCallBack(FNetWebSocketInfoCallBack CallBack) = 0;
	virtual void SetReceiveCallBack(FNetWebSocketPacketReceivedCallBack CallBack) = 0;
	virtual void SetSocketClosedCallBack(FNetWebSocketInfoCallBack CallBack) = 0;

	/** Send raw data to remote end point. */
	virtual bool Send(const uint8* Data, uint32 Size, bool bPrependSize = true) = 0;

	/** service libwebsocket */
	virtual void Tick() = 0;

	/** service libwebsocket until outgoing buffer is empty */
	virtual void Flush() = 0;

	/** Helper functions to describe end points. */
	virtual TArray<uint8> GetRawRemoteAddr(int32& OutPort) = 0;
	virtual FString RemoteEndPoint(bool bAppendPort) = 0;
	virtual FString LocalEndPoint(bool bAppendPort) = 0;
	virtual struct sockaddr_in* GetRemoteAddr() = 0;
};
// Copyright Epic Games, Inc. All Rights Reserved.
//
// Read http://lucumr.pocoo.org/2012/9/24/websockets-101/ for a nice intro to web sockets.
// This uses https://libwebsockets.org/trac/libwebsockets
#pragma  once
#include "IServerWebSocket.h"
#include "ServerWebSocketPrivate.h"

class SERVERWEBSOCKET_API FServerWebSocket : public IServerWebSocket
{
public:

	FServerWebSocket() = default;
	
	//~ Begin IWebSocketServer interface
	virtual ~FServerWebSocket() override;
	virtual void EnableHTTPServer(TArray<FNetWebSocketHttpMount> DirectoriesToServe) override;
	virtual bool Init(uint32 Port, FNetWebSocketClientConnectedCallBack) override;
	virtual void Tick() override;
	virtual FString Info() override;
	//~ End IWebSocketServer interface

	bool IsHttpEnabled() const;

// this was made public because of cross-platform build issues
public:

	/** Callback for a new websocket connection to the server */
	FNetWebSocketClientConnectedCallBack  ConnectedCallBack;

	/** Internal libwebsocket context */
	WebSocketInternalContext* Context;

	/** Protocols serviced by this implementation */
	WebSocketInternalProtocol* Protocols;

	friend class FNetWebSocket;

	uint32 ServerPort;

private:
	bool bEnableHttp = false;

	TArray<FNetWebSocketHttpMount> DirectoriesToServe;
	WebSocketInternalHttpMount* LwsHttpMounts = NULL;
};



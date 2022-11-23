// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleInterface.h"
#include "Templates/UniquePtr.h"
#include "Templates/SharedPointer.h"


class IServerWebSocket;
class INetWebSocket;

/* 
 * Module for web socket server implementation
 */
class SERVERWEBSOCKET_API FServerWebSocketModule : public IModuleInterface
{

public:

	/**
	 * Called when WebSockets module is loaded
	 * Initialize implementation specific parts of WebSockets handling
	 */
	virtual void StartupModule() override;

	/**
	 * Called when WebSockets module is unloaded
	 * Shutdown implementation specific parts of WebSockets handling
	 */
	virtual void ShutdownModule() override;

	/**
	 * Singleton-like access to this module's interface.  This is just for convenience!
	 * Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already.
	 *
	 * @return Returns singleton instance, loading the module on demand if needed
	 */
	static FServerWebSocketModule& Get();

	/**
	 * Create a WebSocket server.
	 *
	 * @return A new WebSocket server, or nullptr if the server couldn't be created.
	 */
	virtual TUniquePtr<IServerWebSocket> CreateServer();

private:

	/** singleton for the module while loaded and available */
	static FServerWebSocketModule* Singleton;
};

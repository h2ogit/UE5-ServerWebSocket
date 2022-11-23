// Copyright Epic Games, Inc. All Rights Reserved.

namespace UnrealBuildTool.Rules
{
	public class ServerWebSocket : ModuleRules
	{
		public ServerWebSocket(ReadOnlyTargetRules Target) : base(Target)
		{
			PublicDependencyModuleNames.AddRange(
				new string[]
                {
					"Engine"
                }
			);

			PrivateDependencyModuleNames.AddRange(
				new string[] {
					"Core",
					"CoreUObject",
					"NetCore",
					"EngineSettings",
					"ImageCore",
					"Sockets",
					"PacketHandler",
					"OpenSSL",
					"libWebSockets",
					"zlib"
				}
			);

			PublicDefinitions.Add("USE_LIBWEBSOCKET=1");
		}
	}
}

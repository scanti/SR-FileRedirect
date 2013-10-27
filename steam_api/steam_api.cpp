#include "stdafx.h"

#include <Shellapi.h>

#include "steam_api.h"
#include "iat_functions.h"
#include "Hooks.h"
#include "FileLogger.h"

using namespace std;

//#define SRTT

#ifdef SRTT
	#pragma comment (linker, "/export:GetHSteamPipe=steam_old.GetHSteamPipe,@1")
	#pragma comment (linker, "/export:GetHSteamUser=steam_old.GetHSteamUser,@2")
	#pragma comment (linker, "/export:SteamAPI_GetHSteamPipe=steam_old.SteamAPI_GetHSteamPipe,@3")
	#pragma comment (linker, "/export:SteamAPI_GetHSteamUser=steam_old.SteamAPI_GetHSteamUser,@4")
	#pragma comment (linker, "/export:SteamAPI_GetSteamInstallPath=steam_old.SteamAPI_GetSteamInstallPath,@5")
	#pragma comment (linker, "/export:SteamAPI_Init=steam_old.SteamAPI_Init,@6")
	#pragma comment (linker, "/export:SteamAPI_InitSafe=steam_old.SteamAPI_InitSafe,@7")
	#pragma comment (linker, "/export:SteamAPI_IsSteamRunning=steam_old.SteamAPI_IsSteamRunning,@8")
	#pragma comment (linker, "/export:SteamAPI_RegisterCallResult=steam_old.SteamAPI_RegisterCallResult,@9")
	#pragma comment (linker, "/export:SteamAPI_RegisterCallback=steam_old.SteamAPI_RegisterCallback,@10")
	#pragma comment (linker, "/export:SteamAPI_RestartAppIfNecessary=steam_old.SteamAPI_RestartAppIfNecessary,@11")
	#pragma comment (linker, "/export:SteamAPI_RunCallbacks=steam_old.SteamAPI_RunCallbacks,@12")
	#pragma comment (linker, "/export:SteamAPI_SetMiniDumpComment=steam_old.SteamAPI_SetMiniDumpComment,@13")
	#pragma comment (linker, "/export:SteamAPI_SetTryCatchCallbacks=steam_old.SteamAPI_SetTryCatchCallbacks,@14")
	#pragma comment (linker, "/export:SteamAPI_Shutdown=steam_old.SteamAPI_Shutdown,@15")
	#pragma comment (linker, "/export:SteamAPI_UnregisterCallResult=steam_old.SteamAPI_UnregisterCallResult,@16")
	#pragma comment (linker, "/export:SteamAPI_UnregisterCallback=steam_old.SteamAPI_UnregisterCallback,@17")
	#pragma comment (linker, "/export:SteamAPI_UseBreakpadCrashHandler=steam_old.SteamAPI_UseBreakpadCrashHandler,@18")
	#pragma comment (linker, "/export:SteamAPI_WriteMiniDump=steam_old.SteamAPI_WriteMiniDump,@19")
	#pragma comment (linker, "/export:SteamApps=steam_old.SteamApps,@20")
	#pragma comment (linker, "/export:SteamClient=steam_old.SteamClient,@21")
	#pragma comment (linker, "/export:SteamContentServer=steam_old.SteamContentServer,@22")
	#pragma comment (linker, "/export:SteamContentServerUtils=steam_old.SteamContentServerUtils,@23")
	#pragma comment (linker, "/export:SteamContentServer_Init=steam_old.SteamContentServer_Init,@24")
	#pragma comment (linker, "/export:SteamContentServer_RunCallbacks=steam_old.SteamContentServer_RunCallbacks,@25")
	#pragma comment (linker, "/export:SteamContentServer_Shutdown=steam_old.SteamContentServer_Shutdown,@26")
	#pragma comment (linker, "/export:SteamFriends=steam_old.SteamFriends,@27")
	#pragma comment (linker, "/export:SteamGameServer=steam_old.SteamGameServer,@28")
	#pragma comment (linker, "/export:SteamGameServerApps=steam_old.SteamGameServerApps,@29")
	#pragma comment (linker, "/export:SteamGameServerNetworking=steam_old.SteamGameServerNetworking,@30")
	#pragma comment (linker, "/export:SteamGameServerStats=steam_old.SteamGameServerStats,@31")
	#pragma comment (linker, "/export:SteamGameServerUtils=steam_old.SteamGameServerUtils,@32")
	#pragma comment (linker, "/export:SteamGameServer_BSecure=steam_old.SteamGameServer_BSecure,@33")
	#pragma comment (linker, "/export:SteamGameServer_GetHSteamPipe=steam_old.SteamGameServer_GetHSteamPipe,@34")
	#pragma comment (linker, "/export:SteamGameServer_GetHSteamUser=steam_old.SteamGameServer_GetHSteamUser,@35")
	#pragma comment (linker, "/export:SteamGameServer_GetIPCCallCount=steam_old.SteamGameServer_GetIPCCallCount,@36")
	#pragma comment (linker, "/export:SteamGameServer_GetSteamID=steam_old.SteamGameServer_GetSteamID,@37")
	#pragma comment (linker, "/export:SteamGameServer_Init=steam_old.SteamGameServer_Init,@38")
	#pragma comment (linker, "/export:SteamGameServer_InitSafe=steam_old.SteamGameServer_InitSafe,@39")
	#pragma comment (linker, "/export:SteamGameServer_RunCallbacks=steam_old.SteamGameServer_RunCallbacks,@40")
	#pragma comment (linker, "/export:SteamGameServer_Shutdown=steam_old.SteamGameServer_Shutdown,@41")
	#pragma comment (linker, "/export:SteamMasterServerUpdater=steam_old.SteamMasterServerUpdater,@42")
	#pragma comment (linker, "/export:SteamMatchmaking=steam_old.SteamMatchmaking,@43")
	#pragma comment (linker, "/export:SteamMatchmakingServers=steam_old.SteamMatchmakingServers,@44")
	#pragma comment (linker, "/export:SteamNetworking=steam_old.SteamNetworking,@45")
	#pragma comment (linker, "/export:SteamRemoteStorage=steam_old.SteamRemoteStorage,@46")
	#pragma comment (linker, "/export:SteamUser=steam_old.SteamUser,@47")
	#pragma comment (linker, "/export:SteamUserStats=steam_old.SteamUserStats,@48")
	#pragma comment (linker, "/export:SteamUtils=steam_old.SteamUtils,@49")
	#pragma comment (linker, "/export:Steam_GetHSteamUserCurrent=steam_old.Steam_GetHSteamUserCurrent,@50")
	#pragma comment (linker, "/export:Steam_RegisterInterfaceFuncs=steam_old.Steam_RegisterInterfaceFuncs,@51")
	#pragma comment (linker, "/export:Steam_RunCallbacks=steam_old.Steam_RunCallbacks,@52")
	#pragma comment (linker, "/export:g_pSteamClientGameServer=steam_old.g_pSteamClientGameServer,@53")
#else
	#pragma comment (linker, "/export:GetHSteamPipe=steam_old.GetHSteamPipe,@1")
	#pragma comment (linker, "/export:GetHSteamUser=steam_old.GetHSteamUser,@2")
	#pragma comment (linker, "/export:SteamAPI_GetHSteamPipe=steam_old.SteamAPI_GetHSteamPipe,@3")
	#pragma comment (linker, "/export:SteamAPI_GetHSteamUser=steam_old.SteamAPI_GetHSteamUser,@4")
	#pragma comment (linker, "/export:SteamAPI_GetSteamInstallPath=steam_old.SteamAPI_GetSteamInstallPath,@5")
	#pragma comment (linker, "/export:SteamAPI_Init=steam_old.SteamAPI_Init,@6")
	#pragma comment (linker, "/export:SteamAPI_InitSafe=steam_old.SteamAPI_InitSafe,@7")
	#pragma comment (linker, "/export:SteamAPI_IsSteamRunning=steam_old.SteamAPI_IsSteamRunning,@8")
	#pragma comment (linker, "/export:SteamAPI_RegisterCallResult=steam_old.SteamAPI_RegisterCallResult,@9")
	#pragma comment (linker, "/export:SteamAPI_RegisterCallback=steam_old.SteamAPI_RegisterCallback,@10")
	#pragma comment (linker, "/export:SteamAPI_RestartAppIfNecessary=steam_old.SteamAPI_RestartAppIfNecessary,@11")
	#pragma comment (linker, "/export:SteamAPI_RunCallbacks=steam_old.SteamAPI_RunCallbacks,@12")
	#pragma comment (linker, "/export:SteamAPI_SetBreakpadAppID=steam_old.SteamAPI_SetBreakpadAppID,@13")
	#pragma comment (linker, "/export:SteamAPI_SetMiniDumpComment=steam_old.SteamAPI_SetMiniDumpComment,@14")
	#pragma comment (linker, "/export:SteamAPI_SetTryCatchCallbacks=steam_old.SteamAPI_SetTryCatchCallbacks,@15")
	#pragma comment (linker, "/export:SteamAPI_Shutdown=steam_old.SteamAPI_Shutdown,@16")
	#pragma comment (linker, "/export:SteamAPI_UnregisterCallResult=steam_old.SteamAPI_UnregisterCallResult,@17")
	#pragma comment (linker, "/export:SteamAPI_UnregisterCallback=steam_old.SteamAPI_UnregisterCallback,@18")
	#pragma comment (linker, "/export:SteamAPI_UseBreakpadCrashHandler=steam_old.SteamAPI_UseBreakpadCrashHandler,@19")
	#pragma comment (linker, "/export:SteamAPI_WriteMiniDump=steam_old.SteamAPI_WriteMiniDump,@20")
	#pragma comment (linker, "/export:SteamApps=steam_old.SteamApps,@21")
	#pragma comment (linker, "/export:SteamClient=steam_old.SteamClient,@22")
	#pragma comment (linker, "/export:SteamContentServer=steam_old.SteamContentServer,@23")
	#pragma comment (linker, "/export:SteamContentServerUtils=steam_old.SteamContentServerUtils,@24")
	#pragma comment (linker, "/export:SteamContentServer_Init=steam_old.SteamContentServer_Init,@25")
	#pragma comment (linker, "/export:SteamContentServer_RunCallbacks=steam_old.SteamContentServer_RunCallbacks,@26")
	#pragma comment (linker, "/export:SteamContentServer_Shutdown=steam_old.SteamContentServer_Shutdown,@27")
	#pragma comment (linker, "/export:SteamFriends=steam_old.SteamFriends,@28")
	#pragma comment (linker, "/export:SteamGameServer=steam_old.SteamGameServer,@29")
	#pragma comment (linker, "/export:SteamGameServerApps=steam_old.SteamGameServerApps,@30")
	#pragma comment (linker, "/export:SteamGameServerHTTP=steam_old.SteamGameServerHTTP,@31")
	#pragma comment (linker, "/export:SteamGameServerNetworking=steam_old.SteamGameServerNetworking,@32")
	#pragma comment (linker, "/export:SteamGameServerStats=steam_old.SteamGameServerStats,@33")
	#pragma comment (linker, "/export:SteamGameServerUtils=steam_old.SteamGameServerUtils,@34")
	#pragma comment (linker, "/export:SteamGameServer_BSecure=steam_old.SteamGameServer_BSecure,@35")
	#pragma comment (linker, "/export:SteamGameServer_GetHSteamPipe=steam_old.SteamGameServer_GetHSteamPipe,@36")
	#pragma comment (linker, "/export:SteamGameServer_GetHSteamUser=steam_old.SteamGameServer_GetHSteamUser,@37")
	#pragma comment (linker, "/export:SteamGameServer_GetIPCCallCount=steam_old.SteamGameServer_GetIPCCallCount,@38")
	#pragma comment (linker, "/export:SteamGameServer_GetSteamID=steam_old.SteamGameServer_GetSteamID,@39")
	#pragma comment (linker, "/export:SteamGameServer_Init=steam_old.SteamGameServer_Init,@40")
	#pragma comment (linker, "/export:SteamGameServer_InitSafe=steam_old.SteamGameServer_InitSafe,@41")
	#pragma comment (linker, "/export:SteamGameServer_RunCallbacks=steam_old.SteamGameServer_RunCallbacks,@42")
	#pragma comment (linker, "/export:SteamGameServer_Shutdown=steam_old.SteamGameServer_Shutdown,@43")
	#pragma comment (linker, "/export:SteamHTTP=steam_old.SteamHTTP,@44")
	#pragma comment (linker, "/export:SteamMatchmaking=steam_old.SteamMatchmaking,@45")
	#pragma comment (linker, "/export:SteamMatchmakingServers=steam_old.SteamMatchmakingServers,@46")
	#pragma comment (linker, "/export:SteamNetworking=steam_old.SteamNetworking,@47")
	#pragma comment (linker, "/export:SteamRemoteStorage=steam_old.SteamRemoteStorage,@48")
	#pragma comment (linker, "/export:SteamScreenshots=steam_old.SteamScreenshots,@49")
	#pragma comment (linker, "/export:SteamUser=steam_old.SteamUser,@50")
	#pragma comment (linker, "/export:SteamUserStats=steam_old.SteamUserStats,@51")
	#pragma comment (linker, "/export:SteamUtils=steam_old.SteamUtils,@52")
	#pragma comment (linker, "/export:Steam_GetHSteamUserCurrent=steam_old.Steam_GetHSteamUserCurrent,@53")
	#pragma comment (linker, "/export:Steam_RegisterInterfaceFuncs=steam_old.Steam_RegisterInterfaceFuncs,@54")
	#pragma comment (linker, "/export:Steam_RunCallbacks=steam_old.Steam_RunCallbacks,@55")
	#pragma comment (linker, "/export:g_pSteamClientGameServer=steam_old.g_pSteamClientGameServer,@56")
#endif

BOOL WINAPI DllMain(HINSTANCE hInst,DWORD reason,LPVOID)
{
	switch(reason)
	{
		case DLL_PROCESS_ATTACH:
		{
			HMODULE main_handle;
			char NameBuffer[MAX_PATH];
			void *old_proc;
			int NumArgs;
			LPWSTR *ArgList;
			bool HookLoose=false;
			bool HookMain=false;
			bool Vanilla=false;

			InitLogger("log.txt");
#ifdef SRTT
			PrintLog("Initialize SRTT file redirector...\n");
#else
			PrintLog("Initialize SRIV file redirector...\n");
#endif
			main_handle=GetModuleHandleA(NULL);
			GetModuleFileNameA(main_handle,NameBuffer,260);
			PrintLog("Module name = %s\n",NameBuffer);
			ArgList=CommandLineToArgvW(GetCommandLineW(),&NumArgs);
			for(int i=1;i<NumArgs;i++)
			{
				PrintLog("Command line (%i) = %S\n",i,ArgList[i]);
				if (wcsncmp(ArgList[i],L"-loose:",7)==0)
				{
					WideCharToMultiByte(CP_ACP,0,ArgList[i]+7,-1,NameBuffer,260,NULL,NULL);
					PrintLog("Loose file directory = %s\n",NameBuffer);
					SetLooseDirectory(NameBuffer);
					HookLoose=true;
					continue;
				}
				if(wcsncmp(ArgList[i],L"-loosebase:",11)==0)
				{
					WideCharToMultiByte(CP_ACP,0,ArgList[i]+11,-1,NameBuffer,260,NULL,NULL);
					PrintLog("Base file directory = %s\n",NameBuffer);
					SetMainDirectory(NameBuffer);
					HookMain=true;
					continue;
				}
				if(wcsncmp(ArgList[i],L"-vanilla",8)==0)
				{
					Vanilla=true;
					continue;
				}
			}

			LocalFree(ArgList);

			if(Vanilla)
			{
				HookMain=false;
				HookLoose=false;
			}

			if(HookLoose && !HookMain)
			{
				HookLoose=false;
				HookMain=true;
				SetMainDirectory(GetLooseDirectory());
				SetLooseDirectory(NULL);
			}
			if(!Vanilla)
			{
				if (HookMain && !HookLoose)
				{
					PrintLog("Hooking filing system for Base only redirection.\n");
					if(PatchIat(main_handle,"Kernel32.dll","CreateFileA",
							(void *)MainOnly_CreateFileA,&old_proc)==S_OK)
						PrintLog("Patched Kernel32.CreateFileA\n");

					if(PatchIat(main_handle,"Kernel32.dll","GetFileAttributesExA",
							(void *)MainOnly_GetFileAttributesExA,&old_proc)==S_OK)
						PrintLog("Patched Kernel32.GetFileAttributesExA\n");
				}
			}
			else
			{
				PrintLog("Hooking filing system for Vanilla redirection.\n");
				if(PatchIat(main_handle,"Kernel32.dll","CreateFileA",
						(void *)Vanilla_CreateFileA,&old_proc)==S_OK)
					PrintLog("Patched Kernel32.CreateFileA\n");

				if(PatchIat(main_handle,"Kernel32.dll","GetFileAttributesExA",
						(void *)Vanilla_GetFileAttributesExA,&old_proc)==S_OK)
					PrintLog("Patched Kernel32.GetFileAttributesExA\n");
			}

			if(PatchIat(main_handle,"Kernel32.dll","GetCommandLineA",
					(void *)New_GetCommandLineA,&old_proc)==S_OK)
				PrintLog("Patched Kernel32.GetCommandLineA\n");

			break;
		}	 

		case DLL_THREAD_ATTACH:
		{
			break;
		}

		case DLL_THREAD_DETACH:
		{
			break;
		}

		case DLL_PROCESS_DETACH:
		{
			PrintLog("Perform any necessary cleanup...\n");
			CloseLogger();
			break;
		}

	}
	return TRUE;
}
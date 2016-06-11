#ifndef RAPIDBREEZE_CWINSOCK_H
#define RAPIDBREEZE_CWINSOCK_H
 
#ifdef UNICODE
#undef UNICODE
#endif // 
#ifdef _UNICODE
#undef _UNICODE
#endif // 

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <CommCtrl.h>
#include <algorithm>
#include <winnt.h>
#include <tlhelp32.h>
#include <shlwapi.h>
#include <iostream>
#include <string>
#include <mmsystem.h>
#include <WinInet.h>
#include <time.h>
#include <vector>
#include <debugapi.h>
#include <stdlib.h>  
#include <Winternl.h>
#include <Iphlpapi.h>
#include <VersionHelpers.h>
#include <ShlObj.h>
#include <fstream>
#include <DbgHelp.h>
#include <Psapi.h>
#include <utility>
#include <sstream>
#include <stdio.h>
#include <stdarg.h>
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")
class CWinsock
{
public:
	CWinsock(VOID);
	~CWinsock(VOID);
	
	VOID InitWinsock(VOID);
	VOID Connect(const char* pszServerUrl);
	std::string SendHttpGet(const char* pszFileUrl);
	std::string SendHttpGet(const char*, const char *);
	VOID Disconnect(VOID);
	VOID CleanUp(VOID);
private:
	SOCKET m_ConnectedSocket;
	const char* m_pszConnectedUrl;

}; extern CWinsock g_Winsock;


#endif // !RAPIDBREEZE_CWINSOCK_H
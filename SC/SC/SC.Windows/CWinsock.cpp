
#include "CWinsock.h"
CWinsock g_Winsock;

CWinsock::CWinsock(VOID)
{
	m_ConnectedSocket = INVALID_SOCKET;
}

CWinsock::~CWinsock(VOID)
{
}

VOID CWinsock::InitWinsock(VOID)
{
	WSADATA wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		exit(0);
	}
}

VOID CWinsock::Connect(const char* pszServerUrl)
{
	m_pszConnectedUrl = pszServerUrl;

	addrinfo hints, *pAddrInfo;

	SecureZeroMemory(&hints, sizeof(hints));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	bool bPort;

	if (getaddrinfo(pszServerUrl, "80", &hints, &pAddrInfo) != 0)
	{
		bPort = false;
	}
	if ((m_ConnectedSocket = socket(pAddrInfo->ai_family, pAddrInfo->ai_socktype, pAddrInfo->ai_protocol)) == INVALID_SOCKET)
	{
		freeaddrinfo(pAddrInfo);
		CWinsock::CleanUp();
		exit(0);
	}

	if (connect(m_ConnectedSocket, pAddrInfo->ai_addr, (INT)pAddrInfo->ai_addrlen) != 0)
	{
		freeaddrinfo(pAddrInfo);
		CWinsock::Disconnect();
		CWinsock::CleanUp();
		exit(0);
	}

	freeaddrinfo(pAddrInfo);
}



std::string CWinsock::SendHttpGet(const char* pszFileUrl, const char * post)
{
	std::string cszRet;
	std::string sMsg = "GET ";
	sMsg += pszFileUrl;
	sMsg += "?"; sMsg += post;
	sMsg += " HTTP/1.0\r\nHost: "; // 1.0 statt 1.1 wegen Chunked_transfer_encoding
	sMsg += m_pszConnectedUrl;
	sMsg += "\"\r\n\r\n\"";

	CHAR szRecvBuffer[512];

	if (send(m_ConnectedSocket, sMsg.c_str(), strlen(sMsg.c_str()), 0) == SOCKET_ERROR)
	{
		CWinsock::Disconnect();
		WSACleanup();
		exit(0);
	}

	INT iBytesReceived = 0;
	do
	{
		iBytesReceived = recv(m_ConnectedSocket, szRecvBuffer, sizeof(szRecvBuffer), 0);

		cszRet.append(szRecvBuffer, iBytesReceived);
	} while (iBytesReceived > 0);

	for (int i = 0; i < cszRet.length(); i++)
	{
		if (cszRet[i] == '\r' && cszRet[i + 1] == '\n' && cszRet[i + 2] == '\r' && cszRet[i + 3] == '\n')
			cszRet.erase(0, i + 4);
	}
	return cszRet;
}


std::string CWinsock::SendHttpGet(const char* pszFileUrl)
{
	std::string cszRet;
	std::string sMsg = "GET ";
	sMsg += pszFileUrl;
	sMsg += " HTTP/1.0\r\nHost: ";
	sMsg += m_pszConnectedUrl;
	sMsg += "\"\r\n\r\n\"";

	CHAR szRecvBuffer[512];

	if (send(m_ConnectedSocket, sMsg.c_str(), strlen(sMsg.c_str()), 0) == SOCKET_ERROR)
	{
		CWinsock::Disconnect();
		WSACleanup();
		exit(0);
	}

	INT iBytesReceived = 0;
	do
	{
		iBytesReceived = recv(m_ConnectedSocket, szRecvBuffer, sizeof(szRecvBuffer), 0);

		cszRet.append(szRecvBuffer, iBytesReceived);
	} while (iBytesReceived > 0);

	for (int i = 0; i < cszRet.length(); i++)
	{
		
		if (cszRet[i] == '\r' && cszRet[i + 1] == '\n' && cszRet[i + 2] == '\r' && cszRet[i + 3] == '\n')
			cszRet.erase(0, i + 4);
	}
	return cszRet;
}

VOID CWinsock::Disconnect(VOID)
{
	if (m_ConnectedSocket != INVALID_SOCKET)
	{
		closesocket(m_ConnectedSocket);
		m_ConnectedSocket = INVALID_SOCKET;
	}
}

VOID CWinsock::CleanUp(VOID)
{
	WSACleanup();
}
//---------------------------------------------------------------------------//
//				___________     __   ___  ___      ___                       //
//				|  _______ \   |  | /  /  \  \    /  /                       //
//				|  |           |  |/  /    \  \  /  /                        //
//				|  |_______    |     /      \  \/  /                         //
//				\_________ \   |     |       \    /                          //
//				  _		 |  |  |  |\  \       |  |                           //
//				 | \_____|  |  |  | \  \      |  |                           //
//				 |__________/  |__|  \__\     |__|  Engine.                  //
//                                                                           //
//---------------------------------------------------------------------------//
//                                                                           //
// Name : skyUDPSocket.h                                                     //
// Author: Gavin Barnes                                                      //
//                                                                           //
/// <summary>                                                                //
/// Sockets.                                                                 //
/// </summary>                                                               //
//                                                                           //
//                                                                           //
//---------------------------------------------------------------------------//
//        Copyright 2012 - 2013 Paradoxon-Studios. All Rights Reserved.      //
//---------------------------------------------------------------------------//

#include "stdafx.h"
#include "skyUDPSocket.h"


skyInt startWinsock ( void )
{
	WSADATA wsa;
	return WSAStartup(MAKEWORD(2,0),&wsa);
}

skyResult skyUDPSocket::Spawn(skyUDPSocket** a_cSocket)
{
	// start the winsocks
	skyLong lRC = startWinsock();
	if(lRC != 0) 
		return skyResult::SKY_ERROR;

	// create the socket
	SOCKET uiPtrSocket = socket( AF_INET, SOCK_DGRAM, 0 );
	if(uiPtrSocket == INVALID_SOCKET)
		return skyResult::SKY_INVALID_POINTER;

	*a_cSocket = SKY_NEW skyUDPSocket(uiPtrSocket);

	return SKY_OK;
}

skyResult skyUDPSocket::Connect( skyString a_strIP, skyInt a_iPort )
{
	this->m_strIP = a_strIP;
	this->m_iPort = a_iPort;

	return SKY_OK;
}

skyResult skyUDPSocket::Send( skyString a_strMSG )
{
	skyULong l_ulIPAddr = INADDR_NONE;
	l_ulIPAddr = inet_addr(m_strIP.c_str());
	IN_ADDR test;
	test.S_un.S_addr = l_ulIPAddr;

	SOCKADDR_IN l_Addr;
	l_Addr.sin_family = AF_INET;
	l_Addr.sin_port = htons(m_iPort);
	l_Addr.sin_addr = test;
	

	skyLong l_lRC = sendto(this->m_pSocket, a_strMSG.c_str(), strlen(a_strMSG.c_str()), 0, (SOCKADDR*)&l_Addr, sizeof(SOCKADDR_IN));

	if( l_lRC == SOCKET_ERROR ) {
		SKY_PRINT_CONSOLE("UDPSocket", "Couldn't send message to ip.", 0xFF);
		return SKY_ERROR;
	}

	return SKY_OK;
}

skyUDPSocket::skyUDPSocket( SOCKET a_cSocket )
{
	this->m_pSocket = a_cSocket;
}

skyUDPSocket::~skyUDPSocket( skyVoid )
{
	closesocket(this->m_pSocket);
}
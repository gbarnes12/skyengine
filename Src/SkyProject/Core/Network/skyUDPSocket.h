#pragma once
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

SKY_TODO("Needs to be redone because this is win32 only stuff! or at least -> if def'd to death!!!");

#if defined WIN32
#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>


#pragma comment(lib, "Ws2_32.lib")

skyInt startWinsock ( void );

class skyUDPSocket 
{
	

public:
	static skyResult skyUDPSocket::Spawn(skyUDPSocket** a_cSocket);
	skyUDPSocket::~skyUDPSocket();

	skyResult skyUDPSocket::Connect(skyString a_strIP, skyInt a_iPort);
	
	skyResult skyUDPSocket::Send(skyString a_strMSG);
private:
	SOCKET m_pSocket;
	skyString m_strIP;
	skyInt m_iPort;

	skyUDPSocket::skyUDPSocket(SOCKET a_cSocket);
	
};
#endif
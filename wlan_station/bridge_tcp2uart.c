/*
 * bridge_tcp2uart.c
 *
 *  Created on: 23 αιπε 2015
 *      Author: roy
 */
#include "bridge_tcp2uart.h"

static unsigned char sTxBuffer[30];
static unsigned char sRxBuffer[30];

//****************************************************************************
//
//! \brief Opening a TCP server side socket and receiving data
//!
//! This function opens a TCP socket in Listen mode and waits for an incoming
//!    TCP connection.
//! If a socket connection is established then the function will try to read
//!    1000 TCP packets from the connected client.
//!
//! \param[in] port number on which the server will be listening on
//!
//! \return     0 on success, -1 on error.
//!
//! \note   This function will wait for an incoming connection till
//!                     one is established
//
//****************************************************************************
int BridgeTcp2UartSocketListen( unsigned short usPort )
{
	SlSockAddrIn_t  sAddr;
	SlSockAddrIn_t  sLocalAddr;
	int             iAddrSize;
	int             iSockID;
	int             iStatus;
	int             iNewSockID;
	long            lNonBlocking = 1;
	int i;
	int msgLength;

	//filling the TCP server socket address
	sLocalAddr.sin_family = SL_AF_INET;
	sLocalAddr.sin_port = sl_Htons((unsigned short)usPort);
	sLocalAddr.sin_addr.s_addr = 0;

	// creating a TCP socket
	iSockID = sl_Socket(SL_AF_INET,SL_SOCK_STREAM, 0);
	if( iSockID < 0 )
	{
		// error
		ASSERT_ON_ERROR(TCP_SERVER_FAILED);
	}

	iAddrSize = sizeof(SlSockAddrIn_t);

	// binding the TCP socket to the TCP server address
	iStatus = sl_Bind(iSockID, (SlSockAddr_t *)&sLocalAddr, iAddrSize);
	if( iStatus < 0 )
	{
		// error
		ASSERT_ON_ERROR(sl_Close(iSockID));
		ASSERT_ON_ERROR(TCP_SERVER_FAILED);
	}
	// putting the socket for listening to the incoming TCP connection
	iStatus = sl_Listen(iSockID, 0);
	if( iStatus < 0 )
	{
		ASSERT_ON_ERROR(sl_Close(iSockID));
		ASSERT_ON_ERROR(TCP_SERVER_FAILED);
	}

	// setting socket option to make the socket as non blocking
	iStatus = sl_SetSockOpt(iSockID, SL_SOL_SOCKET, SL_SO_NONBLOCKING,
							&lNonBlocking, sizeof(lNonBlocking));
	if( iStatus < 0 )
	{
		ASSERT_ON_ERROR(sl_Close(iSockID));
		ASSERT_ON_ERROR(TCP_SERVER_FAILED);
	}

	iNewSockID = SL_EAGAIN;
	UART_PRINT("Waiting for Client Request\n\r");

	// waiting for an incoming TCP connection
	while( iNewSockID < 0 )
	{
		// accepts a connection form a TCP client, if there is any
		// otherwise returns SL_EAGAIN
		iNewSockID = sl_Accept(iSockID, ( struct SlSockAddr_t *)&sAddr,
								(SlSocklen_t*)&iAddrSize);
		if( iNewSockID == SL_EAGAIN )
		{
		   MAP_UtilsDelay(10000);
		}
		else if( iNewSockID < 0 )
		{
			// error
			ASSERT_ON_ERROR(sl_Close(iNewSockID));
			ASSERT_ON_ERROR(sl_Close(iSockID));
			ASSERT_ON_ERROR(TCP_SERVER_FAILED);
		}
	}

	UART_PRINT("Waiting for Info\n\r");

	while(1)
	{
		//1. we are already connected read message from tcp check validity
		iStatus = sl_Recv(iNewSockID, sRxBuffer, PROTOCOL_HEADER_SIZE, 0);
		if( iStatus <= 0 )
		{
		  // error
		  ASSERT_ON_ERROR( sl_Close(iNewSockID));
		  ASSERT_ON_ERROR(sl_Close(iSockID));
		  ASSERT_ON_ERROR(TCP_SERVER_FAILED);
		}
		if( sRxBuffer[0] == MESSAGE_PREAMBLE )
		{
			msgLength = sRxBuffer[4];
			iStatus = sl_Recv(iNewSockID, sRxBuffer+PROTOCOL_HEADER_SIZE,sRxBuffer[4]+1, 0);
			if( iStatus <= 0 )
			{
			  // error
			  ASSERT_ON_ERROR( sl_Close(iNewSockID));
			  ASSERT_ON_ERROR(sl_Close(iSockID));
			  ASSERT_ON_ERROR(TCP_SERVER_FAILED);
			}
			if( ProtocolMessageValidateCrc( sRxBuffer, PROTOCOL_HEADER_SIZE + sRxBuffer[4] + 1))
			{
				//2. write message to uart
			}
		}


		//3. read response from uart
		//4. write response to tcp

#if 0
		iStatus = sl_Recv(iNewSockID, sRxBuffer, 6, 0);
		if( iStatus <= 0 )
		{
		  // error
		  ASSERT_ON_ERROR( sl_Close(iNewSockID));
		  ASSERT_ON_ERROR(sl_Close(iSockID));
		  ASSERT_ON_ERROR(TCP_SERVER_FAILED);
		}
		else
		{
			memcpy(sTxBuffer,sRxBuffer,6);
			iStatus = sl_Send(iNewSockID, sTxBuffer, 6, 0);
			if( iStatus <= 0 )
			{
			  // error
			  ASSERT_ON_ERROR( sl_Close(iNewSockID));
			  ASSERT_ON_ERROR(sl_Close(iSockID));
			  ASSERT_ON_ERROR(TCP_SERVER_FAILED);
			}
		}
#endif
	}


	UART_PRINT("While Loop Exit\n\r");

	// close the connected socket after receiving from connected TCP client
	ASSERT_ON_ERROR(sl_Close(iNewSockID));

	// close the listening socket
	ASSERT_ON_ERROR(sl_Close(iSockID));

	return SUCCESS;
}

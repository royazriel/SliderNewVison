/*
 * protocol.c
 *
 * Created: 08/01/2015 09:21:36
 *  Author: roy
 */ 

#include "string.h"
#include "protocol.h"


static uint32 sMiliSecondCount = 0;

ErrorCode ProtocolSendMessage( Sender src, Recipient dst, Opcode opcode, uint8* data, int len )
{
	Message msg;
	ErrorCode err = etErrorCodeSuccess;
	int i;
	
	msg.preamble = MESSAGE_PREAMBLE;
	msg.src = src;
	msg.dst = dst;
	msg.opcode = opcode;
	msg.len = len;
	memcpy( msg.data, data, len );
	
	//calculate crc
	msg.crc = *(uint8*)&msg;  //put first byte of message inside crc
	for( i = 1; i<PROTOCOL_HEADER_SIZE + len; i++) 
	{
		msg.crc ^= *(uint8*)&msg+i;
	}

	//send message
	for( i = 0; i<PROTOCOL_HEADER_SIZE + len + 1 ; i++) 
	{	
#ifdef ATMEL_ENVIORMENT
		usart_putchar(USART_SERIAL, *(uint8*)&msg + i);
#endif
	}
	
	return err;
}

#ifdef ATMEL_ENVIORMENT
ErrorCode ProtocolGetCharFromUSART( uint8* rxByte )
{
	if(usart_rx_is_complete(USART_SERIAL0))				//char on USART0 / MAIN
	{
		*rxByte = usart_get(USART_SERIAL0);
		return etErrorCodeSuccess;
	}
	return etErrorCodeUsartNoData;
}

uint32_t ProtocolGetSystemMiliSecond()
{
	return sMiliSecondCount;   //TODO: timer interrupt of 1ms
}
#endif
#if 0
void ProtocolParseRecievedMessageFromUart( )
{
	static Message rxMessage;
	static int dataIndex = 0;
	uint8 rxByte, crc;
	static uint32 timeofLastByte;
	static MsgState state = etMsgStateWaitingForPreamble;
	int i;
	
	if( !ProtocolGetCharFromUSART( &rxByte) )
	{
		switch(state)
		{
			case etMsgStateWaitingForPreamble:
				rxMessage.preamble = rxByte;
				state = etMsgStateReadingSource;
				break;
			case etMsgStateReadingSource:
				rxMessage.src = rxByte;
				state = etMsgStateReadingDestination;
				break; 
			case etMsgStateReadingDestination:
				rxMessage.dst = rxByte;
				state = etMsgStateReadingOpcode;
				break;
			case etMsgStateReadingOpcode:
				rxMessage.opcode = rxByte;
				state = etMsgStateReadingLength;
			case etMsgStateReadingLength:
				rxMessage.len = rxByte;
				state = eMsgStatetReadingData;
				break;
			case eMsgStatetReadingData:
				rxMessage.data[dataIndex] = rxByte;
				dataIndex++;
				if(dataIndex == rxMessage.len )
				{
					state = etMsgStateReadingCrc;
				}
				break;
			case etMsgStateReadingCrc:
				rxMessage.crc = rxByte;
				//calculate crc
				if(ProtocolMessageValidateCrc( (uint8*)&rxMessage, PROTOCOL_HEADER_SIZE + rxMessage.len))
				{
					ProtocolMessageHandler( &rxMessage );
				}
				state = etMsgStateAfterMessageHandle; //at this point there are two option 1. we already handles the message 2. message was not valid.  in both cases we want to reset the rxbuffer.
				break;
				
		}
		timeofLastByte= ProtocolGetSystemMiliSecond();	
	}
	
	if( (state != etMsgStateWaitingForPreamble && ProtocolGetSystemMiliSecond()- timeofLastByte > USART_PROTOCOL_TIMEOUT) || state == etMsgStateAfterMessageHandle )
	{
		memset( &rxMessage,0, sizeof(Message));
		dataIndex = 0;
		state = etMsgStateWaitingForPreamble;
	}
}
#endif
uint8 ProtocolMessageValidateCrc( uint8* buffer, uint8 length)
{
	uint8 crc;
	int i;

	crc = *buffer;  //put first byte of message inside crc
	for( i = 1; i<length; i++)
	{
		crc ^= buffer[i];
	}
	return (buffer[length] == crc);
}

ErrorCode ProtocolMessageHandler( Message* msg )
{
	ErrorCode err = etErrorCodeSuccess;
	switch( msg->opcode)
	{
		
		case etOpcodeWindowClose:
		break;
	}
	return err;
}

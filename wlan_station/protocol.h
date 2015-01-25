/*
 * protocol.h
 *
 * Created: 08/01/2015 09:22:32
 *  Author: roy
 */ 


#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#include "Types.h"

#define MESSAGE_PREAMBLE	0xF8
#define BLUTOOTH_PROFILE_MESSAGE_SIZE 20
#define PROTOCOL_HEADER_SIZE	5
#define PROTOCOL_CRC_SIZE			1
#define MAX_DATA_SIZE BLUTOOTH_PROFILE_MESSAGE_SIZE - PROTOCOL_HEADER_SIZE - PROTOCOL_CRC_SIZE
#define USART_PROTOCOL_TIMEOUT 10

//TODO: move this error codes to another file called errors for all project
typedef enum 
{
	etErrorCodeSuccess = 0,
	etErrorCodeUsartNoData,
	etErrorCodeHwError,
	etErrorCodeDefineAnyError
}ErrorCode; 	
	
typedef enum {
	etOpcodeWindowClose = 1,
	etOpcodeWindowOpen,
	etOpcodeWindowStop,
	etOpcodeWindowEmergencyStop,
	etOpcodeWindowLock,
	etOpcodeWindowUnlock,
	etOpcodeBatteryState,
	etOpcodeLimitSwitchState,
	etOpcodeStartPairing,
	etOpcodeSaveMac,
	etOpcodeAck,
	etOpcodeLastOpcode
}Opcode;

typedef enum
{
	etMsgStateWaitingForPreamble,
	etMsgStateReadingSource,
	etMsgStateReadingDestination,
	etMsgStateReadingOpcode,
	etMsgStateReadingLength,
	eMsgStatetReadingData,
	etMsgStateReadingCrc,
	etMsgStateAfterMessageHandle	
}MsgState;

typedef enum {
	etRecipientWifiModule = 1,
	etRecipientMaster,
	etRecipientBleFrame,
	etRecipientBleWing,
	etRecipientProx_r,
	etRecipientProx_l,
	etRecipientBroadcast,
	etRecipientLastRecipient
}Recipient;

typedef enum {
	etSenderWifiModule = 1,
	etSenderMaster,
	etSenderBleFrame,
	etSenderBleWing,
	etSenderProx_r,
	etSenderProx_l,
	etSenderBroadcast,
	etSenderLastSender
}Sender;

#pragma pack(1)
typedef struct __Message
{
	uint8 preamble;
	Sender src;
	Recipient dst;
	Opcode opcode;
	uint8 len;
	uint8 data[PROTOCOL_HEADER_SIZE];
	uint8 crc;
}Message;

#pragma pack(1)
typedef struct __BatteryStateInfo
{
	float batteryLevel;
	uint32 bla;
	uint16 blabla;
}BatteryStateInfo;

ErrorCode ProtocolSendMessage( Sender src, Recipient dst, Opcode opcode, uint8* data, int len );
void ProtocolParseRecievedMessage();
uint8 ProtocolMessageValidateCrc( uint8* buffer, uint8 length);
ErrorCode ProtocolMessageHandler( Message* msg );

#endif /* PROTOCOL_H_ */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace TcpSliderProtocol
{
    public enum ErrorCode
    {
        etErrorCodeSuccess = 0,
        etErrorCodeUsartNoData,
        etErrorCodeHwError,
        etErrorCodeDefineAnyError
    };

    public enum Opcode
    {
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
    };

    public enum MsgState
    {
        etMsgStateWaitingForPreamble,
        etMsgStateReadingSource,
        etMsgStateReadingDestination,
        etMsgStateReadingOpcode,
        etMsgStateReadingLength,
        eMsgStatetReadingData,
        etMsgStateReadingCrc,
        etMsgStateAfterMessageHandle	
    };

    public enum Recipient
    {
        etRecipientWifiModule = 1,
        etRecipientMaster,
        etRecipientBleFrame,
        etRecipientBleWing,
        etRecipientProx_r,
        etRecipientProx_l,
        etRecipientBroadcast,
        etRecipientHost,
        etRecipientLastRecipient,
        
    }

    public enum Sender
    {
        etSenderWifiModule = 1,
        etSenderMaster,
        etSenderBleFrame,
        etSenderBleWing,
        etSenderProx_r,
        etSenderProx_l,
        etSenderBroadcast,
        etSenderHost,
        etSenderLastSender
    }

    public class SliderProtocol
    {
        private const byte MESSAGE_PREAMBLE	= 0xF8;
        private const byte BLUTOOTH_PROFILE_MESSAGE_SIZE = 20;
        private const byte PROTOCOL_HEADER_SIZE =	5;
        private const byte PROTOCOL_CRC_SIZE	=	1;
        private const byte MAX_DATA_SIZE =  BLUTOOTH_PROFILE_MESSAGE_SIZE - PROTOCOL_HEADER_SIZE - PROTOCOL_CRC_SIZE;
        private const byte USART_PROTOCOL_TIMEOUT = 10;
        private const byte PREAMBLE_OFFSET = 0;
        private const byte SRC_OFFSET = 1;
        private const byte DST_OFFSET = 2;
        private const byte OPCODE_OFFSET = 3;
        private const byte LEN_OFFSET = 4;

        public static ErrorCode ProtocolSendMessage( Sender src, Recipient dst, Opcode opcode, byte[] data, int len )
        {
	        byte[] rxBuffer = new byte[PROTOCOL_HEADER_SIZE+len+1];
            byte crc;
	        ErrorCode err = ErrorCode.etErrorCodeSuccess;
	
	        rxBuffer[PREAMBLE_OFFSET] = MESSAGE_PREAMBLE;
	        rxBuffer[SRC_OFFSET] = (byte)src;
            rxBuffer[DST_OFFSET] = (byte)dst;
            rxBuffer[OPCODE_OFFSET] = (byte)opcode;
            rxBuffer[LEN_OFFSET] = (byte)len;
	        
            Array.Copy(data, rxBuffer,len);

	
	        //calculate crc
	        crc = rxBuffer[PREAMBLE_OFFSET];  //put first byte of message inside crc
	        for( int i = 1; i<PROTOCOL_HEADER_SIZE + len; i++) 
	        {
		        crc ^= rxBuffer[i];
	        }
            rxBuffer[PROTOCOL_HEADER_SIZE + len] = crc;

            Connection.Send(rxBuffer);
	        
	        return err;
        }
    }
}

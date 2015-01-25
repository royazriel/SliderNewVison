using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace TcpSliderProtocol
{
    public class SliderApi
    {
        public static void SliderOpenWindow()
        {
            byte[] data = new byte[0];
            SliderProtocol.ProtocolSendMessage(Sender.etSenderHost, Recipient.etRecipientWifiModule, Opcode.etOpcodeWindowOpen, data, data.Count());
        }
    }
}

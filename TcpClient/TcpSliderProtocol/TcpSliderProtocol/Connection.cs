using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.Threading;

namespace TcpSliderProtocol
{
    public class StateObject
    {
        // Client socket.
        public Socket workSocket = null;
        // Size of receive buffer.
        public const int BufferSize = 256;
        // Receive buffer.
        public byte[] buffer = new byte[BufferSize];

        public byte[] finalBuffer = new byte[BufferSize];

        public int index = 0;

        public byte readLength;
    }

    public class Connection
    {
        const short defaultPort = 5555;
            // ManualResetEvent instances signal completion.
        private static ManualResetEvent connectDone = 
            new ManualResetEvent(false);
        private static ManualResetEvent sendDone = 
            new ManualResetEvent(false);
        private static ManualResetEvent receiveDone = 
            new ManualResetEvent(false);

        private static byte[] sResponse = new byte[30];

        private static Socket sClient;

        public static void Connect( string ServerIp )
        {
            try {
                    // Establish the remote endpoint for the socket.
                    // The name of the 
                    // remote device is "host.contoso.com".
                    IPAddress ipAddress = IPAddress.Parse(ServerIp);
                    IPEndPoint remoteEP = new IPEndPoint(ipAddress, defaultPort);

                    // Create a TCP/IP socket.
                    sClient = new Socket(AddressFamily.InterNetwork,
                        SocketType.Stream, ProtocolType.Tcp);

                    // Connect to the remote endpoint.
                    sClient.BeginConnect(remoteEP,
                        new AsyncCallback(ConnectCallback), sClient);
                    connectDone.WaitOne();
                } 
                catch (Exception e) 
                {
                    Console.WriteLine(e.ToString());
                }
        }

        private static void ConnectCallback(IAsyncResult ar)
        {
            try
            {
                // Retrieve the socket from the state object.
                Socket client = (Socket)ar.AsyncState;

                // Complete the connection.
                client.EndConnect(ar);

                Console.WriteLine("Socket connected to {0}",
                    client.RemoteEndPoint.ToString());

                // Signal that the connection has been made.
                connectDone.Set();
            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
            }
        }

        public static byte[] Receive( byte length )
        {
            try
            {
                // Create the state object.
                StateObject state = new StateObject();
                state.workSocket = sClient;
                state.readLength = length;

                // Begin receiving the data from the remote device.
                sClient.BeginReceive(state.buffer, 0, StateObject.BufferSize, 0,
                    new AsyncCallback(ReceiveCallback), state);
                receiveDone.WaitOne();
                return sResponse;
            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
                return null;
            }
        }

        private static void ReceiveCallback(IAsyncResult ar)
        {
            try
            {
                // Retrieve the state object and the client socket 
                // from the asynchronous state object.
                StateObject state = (StateObject)ar.AsyncState;
                Socket client = state.workSocket;

                // Read data from the remote device.
                int bytesRead = client.EndReceive(ar);

                if (bytesRead > 0)
                {
                    if (state.index < state.readLength)
                    {
                        // There might be more data, so store the data received so far.
                        Array.Copy(state.buffer, 0, state.finalBuffer, state.index, bytesRead);
                        state.index += bytesRead;
                        // Get the rest of the data.
                        client.BeginReceive(state.buffer, 0, StateObject.BufferSize, 0,
                            new AsyncCallback(ReceiveCallback), state);
                    }
                    if (state.index == state.readLength)
                    {
                        Array.Copy(state.finalBuffer, sResponse, state.index);
                        // Signal that all bytes have been received.
                        receiveDone.Set();
                    }
                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
            }
        }

        public static void Send( byte[] data )
        {
        
            // Begin sending the data to the remote device.
            sClient.BeginSend(data, 0, data.Length, 0,
                new AsyncCallback(SendCallback), sClient);
            sendDone.WaitOne();
        }

        private static void SendCallback(IAsyncResult ar)
        {
            try
            {
                // Retrieve the socket from the state object.
                Socket client = (Socket)ar.AsyncState;

                // Complete sending the data to the remote device.
                int bytesSent = client.EndSend(ar);
                Console.WriteLine("Sent {0} bytes to server.", bytesSent);

                // Signal that all bytes have been sent.
                sendDone.Set();
            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
            }
        }
    }
}

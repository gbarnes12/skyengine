using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;
using System.IO;

namespace Sky.Core.Network
{

    public class skyUDPServer
    {
        IPEndPoint m_cEndpoint;
        EndPoint m_pRemoteEndpoint;
        Socket m_cSocket;

        public static skyResult Spawn(ref skyUDPServer a_cServer)
        {
            try
            {
                Socket l_cSocket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);

                if (l_cSocket == null)
                    return skyResult.SKY_ERROR;

                a_cServer = new skyUDPServer(l_cSocket);
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
                return skyResult.SKY_ERROR;
            }

            return skyResult.SKY_OK;
        }

        private skyUDPServer(Socket a_cSocket)
        {
            this.m_cEndpoint = new IPEndPoint(IPAddress.Any, 1389);
            this.m_pRemoteEndpoint = new IPEndPoint(IPAddress.Any, 1389);
            this.m_cSocket = a_cSocket;
            this.m_cSocket.Bind(m_cEndpoint);
        }

        public bool IsConnected()
        {
            return m_cSocket.Connected;
        }

        public string Process() 
        {
            byte[] l_aData = new byte[1024];
            int recv = m_cSocket.ReceiveFrom( l_aData, ref m_pRemoteEndpoint );

            if (recv != 0)
                return Encoding.ASCII.GetString(l_aData, 0, recv);

            return null;
        }
    }
}

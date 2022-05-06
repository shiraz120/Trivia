using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace GUI_WPF
{
    public class CommunicatorHelper
    {
        private const int DEFAULT_PORT = 8826;
        private const int TYPE_CODE_LENGTH = 1;
        static IPEndPoint serverEndPoint = new IPEndPoint(IPAddress.Parse("127.0.0.1"), DEFAULT_PORT);
        static TcpClient client = new TcpClient();
        static NetworkStream clientStream;
        public CommunicatorHelper()
        {
            client.Connect(serverEndPoint);
            clientStream = client.GetStream();
        }
        static char GetMessageTypeCode()
        {
            byte[] buffer = new byte[TYPE_CODE_LENGTH];
            return Convert.ToChar(clientStream.Read(buffer, 0, TYPE_CODE_LENGTH));
        }
        static string GetStringPartFromSocket(int bytesNum)
        {
            byte[] buffer = new byte[TYPE_CODE_LENGTH];
            Convert.ToString(clientStream.Read(buffer, 0, TYPE_CODE_LENGTH));
        }
    }

}

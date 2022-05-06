using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace GUI_WPF
{
    public class Communicator
    {
        public const char LOGIN_REQUEST = '1';
        public const char SIGNUP_REQUEST = '2';
        const int BYTES_SIZE = 256;
        const int TYPE_CODE_LENGTH = 1;
        const int DEFAULT_PORT = 8826;
        static IPEndPoint serverEndPoint = new IPEndPoint(IPAddress.Parse("127.0.0.1"), DEFAULT_PORT);
        static TcpClient client = new TcpClient();
        static NetworkStream clientStream;
        public static void StartCommunication()
        {
            client.Connect(serverEndPoint);
            clientStream = client.GetStream();
        }
        public static void closeStream()
        {
            clientStream.Close();
        }
        public static string GetMessageTypeCode()
        {
            byte[] buffer = new byte[TYPE_CODE_LENGTH];
            clientStream.Read(buffer, 0, TYPE_CODE_LENGTH);
            return System.Text.Encoding.UTF8.GetString(buffer);
        }
        public static string GetStringPartFromSocket(int bytesNum)
        {
            byte[] buffer = new byte[TYPE_CODE_LENGTH];
            clientStream.Read(buffer, 0, TYPE_CODE_LENGTH);
            return System.Text.Encoding.UTF8.GetString(buffer);
        }
        public static void sendData(string message)
        {
            byte[] buffer = new ASCIIEncoding().GetBytes(message);
            clientStream.Write(buffer, 0, buffer.Length);
            clientStream.Flush();
        }
        public static int convertStringToInt(string msg)
        {
            return (int)(msg[0]) * (BYTES_SIZE* BYTES_SIZE* BYTES_SIZE) + (int)(msg[1]) * (BYTES_SIZE * BYTES_SIZE) + (int)(msg[2]) * BYTES_SIZE + (int)(msg[3]);
        }
        public static int getSizePart(int bytesNum)
        {
            byte[] buffer = new byte[bytesNum];
            clientStream.Read(buffer, 0, bytesNum);
            return convertStringToInt(System.Text.Encoding.UTF8.GetString(buffer));
        }
    }
}

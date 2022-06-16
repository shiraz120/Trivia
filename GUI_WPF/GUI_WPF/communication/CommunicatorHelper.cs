using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace GUI_WPF
{
    public class Communicator
    {
        public const char LOGIN_REQUEST = '1';
        public const char SIGNUP_REQUEST = '2';
        public const char SIGNOUT_REQUEST = '5';
        public const char CREATE_ROOM_REQUEST = '3';
        public const char GET_PERSONAL_STATS_REQUEST = '7';
        public const char GET_PLAYERS_IN_ROOM_REQUEST = '6';
        public const char GET_ROOMS_REQUEST = '4';
        public const char GET_HIGH_SCORE_REQUEST = '8';
        public const char JOIN_ROOM_REQUEST = '9';
        public const char CLOSE_ROOM_REQUEST = 'A';
        public const char GET_ROOM_STATE_REQUEST = 'B';
        public const char START_GAME_REQUEST = 'C';
        public const char LEAVE_ROOM_REQUEST = 'D';
        public const char SUBMIT_ANSWER_REQUEST = 'E';
        public const char LEAVE_GAME_REQUEST = 'F';
        public const char GET_QUESTION_REQUEST = 'G';
        public const char GET_GAME_RESULTS_REQUEST = 'H';
        const int BYTES_SIZE = 256;
        const int TYPE_CODE_LENGTH = 1;
        const int DEFAULT_PORT = 8826;
        static IPEndPoint serverEndPoint = new IPEndPoint(IPAddress.Parse("127.0.0.1"), DEFAULT_PORT);
        static TcpClient client = new TcpClient();
        static NetworkStream clientStream;

        /*
        this function logs out the user from the server
        input: none
        output: none
        */
        public static void logOut()
        {
            sendData(Convert.ToString(LEAVE_GAME_REQUEST) + "\0\0\0\0");
            sendData(Convert.ToString(CLOSE_ROOM_REQUEST) + "\0\0\0\0");
            sendData(Convert.ToString(LEAVE_ROOM_REQUEST) + "\0\0\0\0");
            sendData(Convert.ToString(SIGNOUT_REQUEST) + "\0\0\0\0");
            Application.Current.Shutdown();
        }

        /*
        this function connects to the server
        input: none
        output: none
        */
        public static void StartCommunication()
        {
            try
            {
                client.Connect(serverEndPoint);
                clientStream = client.GetStream();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                System.Environment.Exit(1);
                Communicator.closeStream();
            }
        }

        /*
        this function closes the stream and disconnect from the server
        input: none
        output: none
        */
        public static void closeStream()
        {
            clientStream.Close();
        }

        /*
        this function gets the part of the type code of the message
        input: none
        output: the message type code
        */
        public static string GetMessageTypeCode()
        {
            byte[] buffer = new byte[TYPE_CODE_LENGTH];
            try
            {
                clientStream.Read(buffer, 0, TYPE_CODE_LENGTH);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                System.Environment.Exit(1);
                Communicator.closeStream();
            }
            return System.Text.Encoding.UTF8.GetString(buffer);
        }
        
        /*
        this function gets the string part from the message
        input: the length of the string
        output: the string part from the message
        */
        public static string GetStringPartFromSocket(int bytesNum)
        {
            byte[] buffer = new byte[bytesNum];
            try
            {
                clientStream.Read(buffer, 0, bytesNum);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                System.Environment.Exit(1);
                Communicator.closeStream();
            }
            return System.Text.Encoding.UTF8.GetString(buffer);
        }

        /*
        this function send data to the server
        input: the message
        output: none
        */
        public static void sendData(string message)
        {
            try
            {
                byte[] buffer = new ASCIIEncoding().GetBytes(message);
                clientStream.Write(buffer, 0, buffer.Length);
                clientStream.Flush();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                System.Environment.Exit(1);
                Communicator.closeStream();
            }
        }

        /*
        this function converts string to int
        input: the message
        output: the numbers of the message
        */
        public static int convertStringToInt(string msg)
        {
            return (int)(msg[0]) * (BYTES_SIZE* BYTES_SIZE* BYTES_SIZE) + (int)(msg[1]) * (BYTES_SIZE * BYTES_SIZE) + (int)(msg[2]) * BYTES_SIZE + (int)(msg[3]);
        }

        /*
        this function gets the size of the message from the message
        input: the length
        output: the size in int
        */
        public static int getSizePart(int bytesNum)
        {
            byte[] buffer = new byte[bytesNum];
            try
            {
                clientStream.Read(buffer, 0, bytesNum);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                System.Environment.Exit(1);
                Communicator.closeStream();
            }
            return convertStringToInt(System.Text.Encoding.UTF8.GetString(buffer));
        }
    }
}

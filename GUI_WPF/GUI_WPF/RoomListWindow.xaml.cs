using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Drawing;
using System.Collections;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace GUI_WPF
{
    /// <summary>
    /// Interaction logic for RoomListWindow.xaml
    /// </summary>
    public partial class RoomListWindow : Window
    {
        private bool keepRunning = true;
        private List<RoomData> listOfRooms;
        public RoomListWindow()
        {
            Thread roomsThread = new Thread(getRooms); ;
            roomsThread.Start();
            InitializeComponent();
        }
        public void getRooms()
        {
            while (keepRunning)
            {
                string request = Convert.ToString(Communicator.GET_ROOMS_REQUEST) + "\0\0\0\0";
                Communicator.sendData(request);
                Communicator.GetMessageTypeCode();
                string response = Communicator.GetStringPartFromSocket(Communicator.getSizePart(checkServerResponse.MAX_DATA_SIZE));
                GetRoomsResponse stats = desirializer.deserializeRequest<GetRoomsResponse>(response);
                listOfRooms = stats.rooms;
                roomList.Dispatcher.Invoke(() => { roomList.Items.Clear(); });
                foreach (RoomData room in listOfRooms)
                {
                    roomList.Dispatcher.Invoke(() => { roomList.Items.Add("Id: " + room.id.ToString() + " max players: " + room.maxPlayers.ToString() + " time per question: " + room.timePerQuestion.ToString() + " questions: " + room.numOfQuestionsInGame.ToString()); roomList.DisplayMemberPath = room.id.ToString(); });
                }
                Thread.Sleep(1000);
            }
        }
        public void HandleClosingWindow(object sender, CancelEventArgs e)
        {
            keepRunning = false;
            Communicator.logOut();
        }
        public void HandleClosingWindow(object sender, RoutedEventArgs e)
        {
            keepRunning = false;
            Communicator.logOut();
            Closing -= HandleClosingWindow;
        }
        private void toggleTheme(object sender, RoutedEventArgs e)
        {
            sharedFunctionsBetweenWindows.toggleTheme(sender, e);
        }

        private void mainMenuButton_Click(object sender, RoutedEventArgs e)
        {
            keepRunning = false;
            Closing -= HandleClosingWindow;
            sharedFunctionsBetweenWindows.moveToMenu(this);
        }

        private void roomList_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            //keepRunning = false;
            //Closing -= HandleClosingWindow;
            //JoinRoomRequest request = new JoinRoomRequest { roomId =  };
            //string requestAsString = serializer.serializeResponse<GetPlayersInRoomRequest>(request, Communicator.GET_PLAYERS_IN_ROOM_REQUEST);
            //Communicator.sendData(requestAsString);
            //Communicator.GetMessageTypeCode();
            //string response = Communicator.GetStringPartFromSocket(Communicator.getSizePart(checkServerResponse.MAX_DATA_SIZE));
            //WaitingWindow newStatsWindow = new WaitingWindow();
            //this.Close();
            //newStatsWindow.Show();
        }
    }
}

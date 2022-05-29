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
        private int whereIdStarts = 4;
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
                    roomList.Dispatcher.Invoke(() => { roomList.Items.Add("Id: " + room.id.ToString() + " max players: " + room.maxPlayers.ToString()); });
                }
                Thread.Sleep(2000);
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
            int id = getId(roomList.SelectedItem.ToString());
            JoinRoomRequest request = new JoinRoomRequest { roomId = id };
            Communicator.sendData(serializer.serializeResponse<JoinRoomRequest>(request, Communicator.JOIN_ROOM_REQUEST));
            string response = checkServerResponse.checkIfjoinRoomSucceeded(id);
            joinRoomDataText.Text = response;
            if (response == checkServerResponse.JOINED_ROOM_SUCCEEDED)
            {
                keepRunning = false;
                Closing -= HandleClosingWindow;
                sharedFunctionsBetweenWindows.current_room_id = id;
                WaitingWindow newStatsWindow = new WaitingWindow();
                this.Close();
                newStatsWindow.Show();
            }
        }
        private int getId(string dataAboutRoom)
        {
            int counter = whereIdStarts;
            string idAsString = "";
            while (Char.IsDigit(dataAboutRoom[counter]))
            {
                idAsString += dataAboutRoom[counter];
                counter++;
            }
            return int.Parse(idAsString);
        }
    }
}

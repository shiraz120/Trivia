using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace GUI_WPF
{
    /// <summary>
    /// Interaction logic for AdminRoom.xaml
    /// </summary>
    public partial class AdminRoom : Window
    {
        private bool keepRunning = true;
        private List<string> listOfPlayers;
        public AdminRoom()
        {
            Thread getPlayers = new Thread(() => getPlayersInRoom(sharedFunctionsBetweenWindows.current_room_id)); ;
            getPlayers.Start();
            InitializeComponent();
        }
        protected override void OnMouseLeftButtonDown(MouseButtonEventArgs e)
        {
            base.OnMouseLeftButtonDown(e);
            DragMove();
        }
        public void getPlayersInRoom(int id)
        {
            while (keepRunning)
            {
                GetPlayersInRoomRequest request = new GetPlayersInRoomRequest { roomId = id };
                string requestAsString = serializer.serializeResponse<GetPlayersInRoomRequest>(request, Communicator.GET_PLAYERS_IN_ROOM_REQUEST);
                Communicator.sendData(requestAsString);
                Communicator.GetMessageTypeCode();
                GetPlayersInRoomResponse createRoomResponse = desirializer.deserializeRequest<GetPlayersInRoomResponse>(Communicator.GetStringPartFromSocket(Communicator.getSizePart(checkServerResponse.MAX_DATA_SIZE)));
                listOfPlayers = createRoomResponse.players;
                if (listOfPlayers != null)
                    playersList.Dispatcher.Invoke(() => { playersList.ItemsSource = listOfPlayers; });
                Thread.Sleep(2000);
            }
        }
        public void HandleClosingWindow(object sender, CancelEventArgs e)
        {
            keepRunning = false;
            closeRoom();
            Communicator.logOut();
            Closing -= HandleClosingWindow;
        }
        public void HandleClosingWindow(object sender, RoutedEventArgs e)
        {
            keepRunning = false;
            closeRoom();
            Communicator.logOut();
            Closing -= HandleClosingWindow;
        }
        private void closeRoom()
        {
            Communicator.sendData(Convert.ToString(Communicator.CLOSE_ROOM_REQUEST) + "\0\0\0\0");
            closeRoomResponse response = desirializer.deserializeRequest<closeRoomResponse>(Communicator.GetStringPartFromSocket(Communicator.getSizePart(checkServerResponse.MAX_DATA_SIZE)));
        }
        private void toggleTheme(object sender, RoutedEventArgs e)
        {
            sharedFunctionsBetweenWindows.toggleTheme(sender, e);
        }

        private void createRoomButton_Click(object sender, RoutedEventArgs e)
        {
            Communicator.sendData(Convert.ToString(Communicator.START_GAME_REQUEST) + "\0\0\0\0");
            keepRunning = false;
            /* need to add game window openning */
        }
        
        private void closeRoomButton_Click(object sender, RoutedEventArgs e)
        {
            keepRunning = false;
            closeRoom();
            Closing -= HandleClosingWindow;
            RoomListWindow newRoomListWindow = new RoomListWindow();
            this.Close();
            newRoomListWindow.Show();
        }
    }
}

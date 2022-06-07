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
            InitializeComponent();
            Thread getPlayers = new Thread(() => getPlayersInRoom(sharedFunctionsBetweenWindows.current_room_id)); ;
            getPlayers.Start();
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
                Communicator.sendData(Convert.ToString(Communicator.GET_ROOM_STATE_REQUEST) + "\0\0\0\0");
                string error = checkServerResponse.checkIfErrorResponse();
                if (error == "")
                {
                    getRoomStateResponse createRoomResponse = desirializer.deserializeRequest<getRoomStateResponse>(Communicator.GetStringPartFromSocket(Communicator.getSizePart(checkServerResponse.MAX_DATA_SIZE)));
                    listOfPlayers = createRoomResponse.players;
                    if (listOfPlayers != null)
                        playersList.Dispatcher.Invoke(() => { playersList.ItemsSource = listOfPlayers; });
                }
                Thread.Sleep(3000);
            }
        }
        public void HandleClosingWindow(object sender, CancelEventArgs e)
        {
            closeRoom();
            Communicator.logOut();
        }
        public void HandleClosingWindow(object sender, RoutedEventArgs e)
        {
            closeRoom();
            Communicator.logOut();
            Closing -= HandleClosingWindow;
        }
        private bool closeRoom()
        {
            keepRunning = false;
            Communicator.sendData(Convert.ToString(Communicator.CLOSE_ROOM_REQUEST) + "\0\0\0\0");
            string error = checkServerResponse.checkIfErrorResponse();
            if (error == "")
            {
                closeRoomResponse response = desirializer.deserializeRequest<closeRoomResponse>(Communicator.GetStringPartFromSocket(Communicator.getSizePart(checkServerResponse.MAX_DATA_SIZE)));
                return true;
            }
            MessageBox.Show(error);
            return false;
        }
        private void toggleTheme(object sender, RoutedEventArgs e)
        {
            sharedFunctionsBetweenWindows.toggleTheme(sender, e);
        }

        private void createRoomButton_Click(object sender, RoutedEventArgs e)
        {
            Communicator.sendData(Convert.ToString(Communicator.START_GAME_REQUEST) + "\0\0\0\0");
            string error = checkServerResponse.checkIfErrorResponse();
            if(error == "")
            {
                createRoomResponse createRoomResponse = desirializer.deserializeRequest<createRoomResponse>(Communicator.GetStringPartFromSocket(Communicator.getSizePart(checkServerResponse.MAX_DATA_SIZE)));
                keepRunning = false;
                /* need to add game window openning */
            }
            else
                HandleClosingWindow(null, new CancelEventArgs());
        }
        
        private void closeRoomButton_Click(object sender, RoutedEventArgs e)
        {
            keepRunning = false;
            if(closeRoom())
            {
                Closing -= HandleClosingWindow;
                RoomListWindow newRoomListWindow = new RoomListWindow();
                this.Close();
                newRoomListWindow.Show();
            }
            else
                HandleClosingWindow(null, new CancelEventArgs());
        }
    }
}

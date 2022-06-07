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

        /*
        this function intializes the widow and starts a thread that will check the players in the room
        input: none
        output: none
        */
        public AdminRoom()
        {
            InitializeComponent();
            Thread getPlayers = new Thread(getPlayersInRoom);
            getPlayers.Start();
        }

        /*
        this function makes the window movable
        input: event
        output: none
        */
        protected override void OnMouseLeftButtonDown(MouseButtonEventArgs e)
        {
            base.OnMouseLeftButtonDown(e);
            DragMove();
        }

        /*
        this function is a thread that gets the player from the room 
        input: none
        output: none
        */
        public void getPlayersInRoom()
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

        /*
        this function closing the window
        input: sender and event
        output: none
        */
        public void HandleClosingWindow(object sender, CancelEventArgs e)
        {
            closeRoom();
            Communicator.logOut();
        }

        /*
        this function closing the window
        input: sender and event
        output: none
        */
        public void HandleClosingWindow(object sender, RoutedEventArgs e)
        {
            closeRoom();
            Communicator.logOut();
            Closing -= HandleClosingWindow;
        }

        /*
        this function colses the room
        input: none
        output: bool
        */
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

        /*
        this function toggles the theme
        input: sender and event
        output: none
        */
        private void toggleTheme(object sender, RoutedEventArgs e)
        {
            sharedFunctionsBetweenWindows.toggleTheme(sender, e);
        }

        /*
        this function creates the room
        input: sender and event
        output: none
        */
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

        /*
        this function closes the room
        input: sender and event
        output: none
        */
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

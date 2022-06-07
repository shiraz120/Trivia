using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Threading;
using System.Windows;
using System.Windows.Input;

namespace GUI_WPF
{
    /// <summary>
    /// Interaction logic for WaitingWindow.xaml
    /// </summary>
    public partial class WaitingWindow : Window
    {
        private bool keepRunning = true;
        private List<string> listOfPlayers;

        /*
        this function initialize the window and starts a thread gets the players in the room
        input: none
        output: none
        */
        public WaitingWindow()
        {
            InitializeComponent();
            Thread getPlayers = new Thread(getPlayersInRoom);
            getPlayers.Start();
        }

        /*
        this function gets the players in the room every 2 seconds
        input: none
        output: none
        */
        public void getPlayersInRoom()
        {
            while (keepRunning)
            {
                string requestAsString = Convert.ToString(Communicator.GET_ROOM_STATE_REQUEST) + "\0\0\0\0";
                Communicator.sendData(requestAsString);
                string error = checkServerResponse.checkIfErrorResponse();
                if (error == "Error: request isnt relevant for the current handler.")
                {
                    keepRunning = false;
                    MessageBox.Show(error);
                    Communicator.logOut();
                }
                getRoomStateResponse getRoomStateResponse = desirializer.deserializeRequest<getRoomStateResponse>(Communicator.GetStringPartFromSocket(Communicator.getSizePart(checkServerResponse.MAX_DATA_SIZE)));
                if(getRoomStateResponse.status == (int)checkServerResponse.Status.STATUS_ROOM_DOESNT_EXIST) //if the room has been closed
                {
                    keepRunning = false;
                    MessageBox.Show("The room has been closed by the admin.");
                    replaceWindowOnExit();
                }
                if(getRoomStateResponse.hasGameBegun) //if game begun
                {
                    /* MOVE TO GAME WINDOW */
                    keepRunning = false;
                    MessageBox.Show("GAME BEGUN");
                }
                else
                {
                    listOfPlayers = getRoomStateResponse.players;
                    if (listOfPlayers != null)
                         playersList.Dispatcher.Invoke(() => { playersList.ItemsSource = listOfPlayers; });
                }
                Thread.Sleep(3000);
            }
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
        this function log out of the communicator and stops the thread
        input: sender and event
        output: none
        */
        public void HandleClosingWindow(object sender, CancelEventArgs e)
        {
            keepRunning = false;
            leaveRoom_Click(null, null);
            Communicator.logOut();
        }

        /*
        this function closes the window and stop the thread
        input: sender and event
        output: none
        */
        public void HandleClosingWindow(object sender, RoutedEventArgs e)
        {
            keepRunning = false;
            leaveRoom_Click(null, null);
            Communicator.logOut();
            Closing -= HandleClosingWindow;
        }

        /*
        this function replaces the window on exit
        input: sender and event
        output: none
        */
        public void replaceWindowOnExit()
        {
            Closing -= HandleClosingWindow;
            RoomListWindow newRoomListWindow = new RoomListWindow();
            this.Close();
            newRoomListWindow.Show();
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
        this function leaves the room
        input: sender and event
        output: none
        */
        private void leaveRoom_Click(object sender, RoutedEventArgs e)
        {
            string request = Convert.ToString(Communicator.LEAVE_ROOM_REQUEST) + "\0\0\0\0";
            Communicator.sendData(request);
            string error = checkServerResponse.checkIfErrorResponse();
            if (error == "")
            {
                leaveRoomResponse stats = desirializer.deserializeRequest<leaveRoomResponse>(Communicator.GetStringPartFromSocket(Communicator.getSizePart(checkServerResponse.MAX_DATA_SIZE)));
                replaceWindowOnExit();
            }
            else //fails the leave room
            {
                keepRunning = false;
                MessageBox.Show(error);
                Communicator.logOut();
            }
        }
    }
}

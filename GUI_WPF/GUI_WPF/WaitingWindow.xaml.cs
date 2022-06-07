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
    /// Interaction logic for WaitingWindow.xaml
    /// </summary>
    public partial class WaitingWindow : Window
    {
        private bool keepRunning = true;
        private List<string> listOfPlayers;
        public WaitingWindow()
        {
            InitializeComponent();
            Thread getPlayers = new Thread(() => getPlayersInRoom(sharedFunctionsBetweenWindows.current_room_id)); ;
            getPlayers.Start();
        }
        public void getPlayersInRoom(int id)
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
                if(getRoomStateResponse.status == (int)checkServerResponse.Status.STATUS_ROOM_DOESNT_EXIST)
                {
                    keepRunning = false;
                    MessageBox.Show("The room has been closed by the admin.");
                    replaceWindowOnExit();
                }
                if(getRoomStateResponse.hasGameBegun)
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
        protected override void OnMouseLeftButtonDown(MouseButtonEventArgs e)
        {
            base.OnMouseLeftButtonDown(e);
            DragMove();
        }
        public void HandleClosingWindow(object sender, CancelEventArgs e)
        {
            keepRunning = false;
            leaveRoom_Click(null, null);
            Communicator.logOut();
        }
        public void HandleClosingWindow(object sender, RoutedEventArgs e)
        {
            keepRunning = false;
            leaveRoom_Click(null, null);
            Communicator.logOut();
            Closing -= HandleClosingWindow;
        }
        public void replaceWindowOnExit()
        {
            Closing -= HandleClosingWindow;
            RoomListWindow newRoomListWindow = new RoomListWindow();
            this.Close();
            newRoomListWindow.Show();
        }
        private void toggleTheme(object sender, RoutedEventArgs e)
        {
            sharedFunctionsBetweenWindows.toggleTheme(sender, e);
        }

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
            else
            {
                keepRunning = false;
                MessageBox.Show(error);
                Communicator.logOut();
            }
        }
    }
}

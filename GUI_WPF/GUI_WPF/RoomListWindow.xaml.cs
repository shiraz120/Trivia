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

        /*
        this function starts a thread that will get all rooms
        input: none
        output: none
        */
        public RoomListWindow()
        {
            Thread roomsThread = new Thread(getRooms);
            roomsThread.Start();
            InitializeComponent();
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
        this function gets all the rooms every 2 seconds
        input: none
        output: none
        */
        public void getRooms()
        {
            while (keepRunning)
            {
                string request = Convert.ToString(Communicator.GET_ROOMS_REQUEST) + "\0\0\0\0";
                Communicator.sendData(request);
                string error = checkServerResponse.checkIfErrorResponse();
                if (error == "")
                {
                    string response = Communicator.GetStringPartFromSocket(Communicator.getSizePart(checkServerResponse.MAX_DATA_SIZE));
                    GetRoomsResponse stats = desirializer.deserializeRequest<GetRoomsResponse>(response);
                    listOfRooms = stats.rooms;
                    if(roomList != null)
                        roomList.Dispatcher.Invoke(() => { roomList.Items.Clear(); });
                    foreach (RoomData room in listOfRooms)
                    {
                        roomList.Dispatcher.Invoke(() => { roomList.Items.Add("Id: " + room.id.ToString() + " max players: " + room.maxPlayers.ToString()); });
                    }
                }
                Thread.Sleep(2000);
            }
        }

        /*
        this function closes the thread and logs out of the communicator
        input: sender and event
        output: none
        */
        public void HandleClosingWindow(object sender, CancelEventArgs e)
        {
            keepRunning = false;
            Communicator.logOut();
        }

        /*
        this function closes the window
        input: sender and event
        output: none
        */
        public void HandleClosingWindow(object sender, RoutedEventArgs e)
        {
            keepRunning = false;
            Communicator.logOut();
            Closing -= HandleClosingWindow;
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
        this function closes the thread and goes to the main menu
        input: sender and event
        output: none
        */
        private void mainMenuButton_Click(object sender, RoutedEventArgs e)
        {
            keepRunning = false;
            Closing -= HandleClosingWindow;
            sharedFunctionsBetweenWindows.moveToMenu(this);
        }

        /*
        this function selects the room
        input: sender and event
        output: none
        */
        private void roomList_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if(roomList.SelectedItem != null)
            {
                int id = getId(roomList.SelectedItem.ToString());
                JoinRoomRequest request = new JoinRoomRequest { roomId = id };
                Communicator.sendData(serializer.serializeResponse<JoinRoomRequest>(request, Communicator.JOIN_ROOM_REQUEST));
                joinRoomDataText.Text = checkServerResponse.checkIfErrorResponse();
                if (joinRoomDataText.Text == "")
                {
                    joinRoomDataText.Text = checkServerResponse.checkIfjoinRoomSucceeded(id);
                    if(joinRoomDataText.Text == checkServerResponse.JOINED_ROOM_SUCCEEDED)
                    {
                        keepRunning = false;
                        Closing -= HandleClosingWindow;
                        sharedFunctionsBetweenWindows.current_room_id = id;
                        WaitingWindow newStatsWindow = new WaitingWindow(); //goes to the waiting room window
                        this.Close();
                        newStatsWindow.Show();
                    }
                }
            }
        }

        /*
        this function gets the id
        input: string
        output: id
        */
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

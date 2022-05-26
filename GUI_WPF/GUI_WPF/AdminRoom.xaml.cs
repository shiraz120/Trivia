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
        public void getPlayersInRoom(int id)
        {
            while (keepRunning)
            {
                GetPlayersInRoomRequest request = new GetPlayersInRoomRequest { roomId = id };
                string requestAsString = serializer.serializeResponse<GetPlayersInRoomRequest>(request, Communicator.GET_PLAYERS_IN_ROOM_REQUEST);
                Communicator.sendData(requestAsString);
                Communicator.GetMessageTypeCode();
                string response = Communicator.GetStringPartFromSocket(Communicator.getSizePart(checkServerResponse.MAX_DATA_SIZE));
                GetPlayersInRoomResponse createRoomResponse = desirializer.deserializeRequest<GetPlayersInRoomResponse>(response);
                listOfPlayers = createRoomResponse.players;
                if (listOfPlayers != null)
                    playersList.Dispatcher.Invoke(() => { playersList.ItemsSource = listOfPlayers; });
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

        private void createRoomButton_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("not implemented yet.");
        }
        
        private void closeRoomButton_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("not implemented yet.");
        }
    }
}

using MaterialDesignThemes.Wpf;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
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
    /// Interaction logic for CreateRoomWindow.xaml
    /// </summary>
    public partial class CreateRoomWindow : Window
    {
        private readonly string INVALID_TIME = "Amount of time for answer cannot be less than 1s.";
        private readonly string INVALID_NAME = "Name of room cannot be empty.";
        private readonly string INVALID_AMOUNT_OF_PLAYERS = "Room must have 2 players or more.";
        private readonly string INVALID_AMOUNT_OF_QUESTIONS = "choose amount of questions.";
        private readonly string CREATE_ROOM_SUCCEEDED = "created room successfully!";
        public CreateRoomWindow()
        {
            InitializeComponent();
        }
        public void HandleClosingWindow(object sender, CancelEventArgs e)
        {
            Communicator.logOut();
        }
        private void toggleTheme(object sender, RoutedEventArgs e)
        {
            sharedFunctionsBetweenWindows.toggleTheme(sender, e);
        }
        private void menuButton_Click(object sender, RoutedEventArgs e)
        {
            Closing -= HandleClosingWindow;
            sharedFunctionsBetweenWindows.moveToMenu(this);
        }
        public void HandleClosingWindow(object sender, RoutedEventArgs e)
        {
            Communicator.logOut();
            Closing -= HandleClosingWindow;
        }
        protected override void OnMouseLeftButtonDown(MouseButtonEventArgs e)
        {
            base.OnMouseLeftButtonDown(e);
            DragMove();
        }

        private void createButton_Click(object sender, RoutedEventArgs e)
        {
            if (string.IsNullOrWhiteSpace(txtTime.Text) || int.Parse(txtTime.Text) <= 0)
                createRoomDataText.Text = INVALID_TIME;
            else if (string.IsNullOrWhiteSpace(txtRoomname.Text))
                createRoomDataText.Text = INVALID_NAME;
            else if (string.IsNullOrWhiteSpace(txtPlayers.Text) || int.Parse(txtPlayers.Text) < 2)
                createRoomDataText.Text = INVALID_AMOUNT_OF_PLAYERS;
            else if (amountOfQuestions.SelectedIndex <= -1)
                createRoomDataText.Text = INVALID_AMOUNT_OF_QUESTIONS;
            else
            {
                createRoomRequest request = new createRoomRequest
                {
                    roomName = txtRoomname.Text,
                    answerTimeout = int.Parse(txtTime.Text),
                    maxUsers = int.Parse(txtPlayers.Text),
                    questionCount = amountOfQuestions.SelectedIndex + 1
                };
                Communicator.sendData(serializer.serializeResponse<createRoomRequest>(request, Communicator.CREATE_ROOM_REQUEST));
                createRoomDataText.Text = checkServerResponse.checkIfErrorResponse();
                if (createRoomDataText.Text == "")
                {
                    createRoomResponse createRoomResponse = desirializer.deserializeRequest<createRoomResponse>(Communicator.GetStringPartFromSocket(Communicator.getSizePart(checkServerResponse.MAX_DATA_SIZE)));
                    sharedFunctionsBetweenWindows.current_room_id = createRoomResponse.status;
                    createRoomDataText.Text = CREATE_ROOM_SUCCEEDED;
                    createRoomDataText.Foreground = System.Windows.Media.Brushes.Green;
                    Closing -= HandleClosingWindow;
                    AdminRoom newAdminWindow = new AdminRoom();
                    this.Close();
                    newAdminWindow.Show();
                }
            }
        }
    }

}

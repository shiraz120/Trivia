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
    /// Interaction logic for ScoreboardWindow.xaml
    /// </summary>
    public partial class ScoreboardWindow : Window
    {
        /*
        this function prints the scoreboard and initialize the window
        input: none
        output: none
        */
        public ScoreboardWindow()
        {
            InitializeComponent();
            int highestScore = 0;
            string winnerUsername = "";
            string request = Convert.ToString(Communicator.GET_GAME_RESULTS_REQUEST) + "\0\0\0\0";
            Communicator.sendData(request);
            string error = checkServerResponse.checkIfErrorResponse();
            if (error == "")
            {
                getGameResultsResponse results = desirializer.deserializeRequest<getGameResultsResponse>(Communicator.GetStringPartFromSocket(Communicator.getSizePart(checkServerResponse.MAX_DATA_SIZE)));
                winnerUsername = results.results[0].username;
                highestScore = results.results[0].correctAnswerCount * 1000 + 250 / results.results[0].averageAnswerTime;
                foreach (var item in results.results)
                {
                    usersList.Items.Add(item.username + " - " + item.correctAnswerCount + " - " + item.averageAnswerTime);
                    if (item.correctAnswerCount * 1000 + 250 / item.averageAnswerTime > highestScore)
                    {
                        highestScore = item.correctAnswerCount * 1000 + 250 / item.averageAnswerTime;
                        winnerUsername = item.username;
                    }
                }
                winner.Text = "Winner: " + winnerUsername;
            }
            else if (error == "Error: request isnt relevant for the current handler.")
            {
                HandleClosingWindow(null, new CancelEventArgs());
            }
            else
            {
                highScoreDataText.Foreground = System.Windows.Media.Brushes.Red;
                highScoreDataText.Text = error;
            }
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
        this function logs out of the communicator
        input: sender and event
        output: none
        */
        public void HandleClosingWindow(object sender, CancelEventArgs e)
        {
            Communicator.logOut();
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
        this function closes the window
        input: sender and event
        output: none
        */
        public void HandleClosingWindow(object sender, RoutedEventArgs e)
        {
            Communicator.logOut();
            Closing -= HandleClosingWindow;
        }

        /*
        this function closes the window and opens the menu
        input: sender and event
        output: none
        */
        private void mainMenuButton_Click(object sender, RoutedEventArgs e)
        {
            Closing -= HandleClosingWindow;
            sharedFunctionsBetweenWindows.moveToMenu(this);
        }
    }
}

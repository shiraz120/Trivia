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
    /// Interaction logic for ScoreboardWindow.xaml
    /// </summary>
    public partial class ScoreboardWindow : Window
    {
        private const int gameNotOver = 0;
        /*
        this function prints the scoreboard and initialize the window
        input: none
        output: none
        */
        public ScoreboardWindow()
        {
            InitializeComponent();
            Thread getResults = new Thread(updateGameResults);
            getResults.Start();
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
        this function closes the window and opens the menu
        input: sender and event
        output: none
        */
        private void mainMenuButton_Click(object sender, RoutedEventArgs e)
        {
            sharedFunctionsBetweenWindows.moveToMenu(this);
        }

        private void updateGameResults()
        {
            string request = "";
            string error = "";
            getGameResultsResponse results;
            do
            {
                request = Convert.ToString(Communicator.GET_GAME_RESULTS_REQUEST) + "\0\0\0\0";
                Communicator.sendData(request);
                error = checkServerResponse.checkIfErrorResponse();
                if (error != "")
                {
                    MessageBox.Show(error);
                    Application.Current.Shutdown();
                }
                results = desirializer.deserializeRequest<getGameResultsResponse>(Communicator.GetStringPartFromSocket(Communicator.getSizePart(checkServerResponse.MAX_DATA_SIZE)));
                Thread.Sleep(3000);
            } while (results.status == gameNotOver);
            int highestScore = 0;
            string winnerUsername = "";
            highScoreDataText.Dispatcher.Invoke(() => { highScoreDataText.Text = ""; });
            winnerUsername = results.results[0].username;
            if (results.results[0].averageAnswerTime == 0)
                highestScore = results.results[0].correctAnswerCount * 1000;
            else
                highestScore = Convert.ToInt32(results.results[0].correctAnswerCount * 1000.0 + (250.0 / results.results[0].averageAnswerTime));
            foreach (var item in results.results)
            {
                usersList.Dispatcher.Invoke(() => { usersList.Items.Add(item.username + " - " + item.correctAnswerCount + " - " + item.averageAnswerTime); } );
                if (item.correctAnswerCount * 1000 + 250 / item.averageAnswerTime > highestScore)
                {
                    if (results.results[0].averageAnswerTime == 0)
                        highestScore = results.results[0].correctAnswerCount * 1000;
                    else
                        highestScore = Convert.ToInt32(results.results[0].correctAnswerCount * 1000 + 250 / results.results[0].averageAnswerTime);
                    winnerUsername = item.username;
                }
            }
            winner.Dispatcher.Invoke(() => { winner.Text = "Winner: " + winnerUsername; });
        }

        /*
        this function closes the thread and logs out of the communicator
        input: sender and event
        output: none
        */
        private void exitBtnClick(object sender, RoutedEventArgs e)
        {
            Application.Current.Shutdown();
        }
    }
}

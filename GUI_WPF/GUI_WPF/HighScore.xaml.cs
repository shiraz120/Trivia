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
    /// Interaction logic for HighScore.xaml
    /// </summary>
    public partial class HighScore : Window
    {
        /*
        this function initialize the window, gets top users and shows them
        input: none
        output: none
        */
        public HighScore()
        {
            InitializeComponent();
            string request = Convert.ToString(Communicator.GET_HIGH_SCORE_REQUEST) + "\0\0\0\0";
            Communicator.sendData(request);
            string error = checkServerResponse.checkIfErrorResponse();
            if (error == "")
            {
                getHighScoreResponse stats = desirializer.deserializeRequest<getHighScoreResponse>(Communicator.GetStringPartFromSocket(Communicator.getSizePart(checkServerResponse.MAX_DATA_SIZE)));
                foreach(var item in stats.statistics)
                {
                    highestUsers.Items.Add(item.Key + " - " + Convert.ToString(item.Value));
                }
            }
            else if(error == "Error: request isnt relevant for the current handler.")
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
        this function goes to the statistics menu
        input: sender and event
        output: none
        */
        private void statisticsMenuButton_Click(object sender, RoutedEventArgs e)
        {
            Closing -= HandleClosingWindow;
            StatisticsMenu newStatsWindow = new StatisticsMenu();
            this.Close();
            newStatsWindow.Show();
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
    }
}

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
        public HighScore()
        {
            InitializeComponent();
            string request = Convert.ToString(Communicator.GET_HIGH_SCORE_REQUEST) + "\0\0\0\0";
            Communicator.sendData(request);
            string error = checkServerResponse.checkIfErrorResponse();
            if (error != "")
            {
                highScoreDataText.Foreground = System.Windows.Media.Brushes.Red;
                highScoreDataText.Text = error;
            }
            else
            {
                getHighScoreResponse stats = desirializer.deserializeRequest<getHighScoreResponse>(Communicator.GetStringPartFromSocket(Communicator.getSizePart(checkServerResponse.MAX_DATA_SIZE)));
                foreach(var item in stats.statistics)
                {
                    highestUsers.Items.Add(item.Key + " - " + Convert.ToString(item.Value));
                }
            }
        }
        protected override void OnMouseLeftButtonDown(MouseButtonEventArgs e)
        {
            base.OnMouseLeftButtonDown(e);
            DragMove();
        }
        private void toggleTheme(object sender, RoutedEventArgs e)
        {
            sharedFunctionsBetweenWindows.toggleTheme(sender, e);
        }
        public void HandleClosingWindow(object sender, CancelEventArgs e)
        {
            Communicator.logOut();
        }
        private void statisticsMenuButton_Click(object sender, RoutedEventArgs e)
        {
            Closing -= HandleClosingWindow;
            StatisticsMenu newStatsWindow = new StatisticsMenu();
            this.Close();
            newStatsWindow.Show();
        }
        public void HandleClosingWindow(object sender, RoutedEventArgs e)
        {
            Communicator.logOut();
            Closing -= HandleClosingWindow;
        }
    }
}

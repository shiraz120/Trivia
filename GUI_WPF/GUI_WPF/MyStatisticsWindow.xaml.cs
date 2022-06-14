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
    /// Interaction logic for Window1.xaml
    /// </summary>
    public partial class MyStatisticsWindow : Window
    {
        const int CorrectAnswersIndex = 2;
        const int totalAnswersIndex = 3;
        const int amountOfGamesIndex = 1;
        const int avgAnswerTimeIndex = 4;

        /*
        this function initialize the window and writes the statistics
        input: none
        output: none
        */
        public MyStatisticsWindow()
        {
            InitializeComponent();
            Communicator.sendData(Convert.ToString(Communicator.GET_PERSONAL_STATS_REQUEST) + "\0\0\0\0");
            string error = checkServerResponse.checkIfErrorResponse();
            if (error == "")
            {
                getPersonalStatsResponse stats = desirializer.deserializeRequest<getPersonalStatsResponse>(Communicator.GetStringPartFromSocket(Communicator.getSizePart(checkServerResponse.MAX_DATA_SIZE)));
                Title.Text = stats.statistics[0] + " Statistics";
                avgTimeForAnswer.Text = avgTimeForAnswer.Text + "      " + stats.statistics[avgAnswerTimeIndex];
                amountOfWrongAnswers.Text = amountOfWrongAnswers.Text + "      " + Convert.ToString(int.Parse(stats.statistics[totalAnswersIndex]) - int.Parse(stats.statistics[CorrectAnswersIndex]));
                amountOfCorrectAnswers.Text = amountOfCorrectAnswers.Text + "      " + stats.statistics[CorrectAnswersIndex];
                amountOfGames.Text = amountOfGames.Text + "      " + stats.statistics[amountOfGamesIndex];
            }
            else if (error == "Error: request isnt relevant for the current handler.")
            {
                Application.Current.Shutdown();
            }
            else
            {
                statisticsDataText.Foreground = System.Windows.Media.Brushes.Red;
                statisticsDataText.Text = error;
            }
        }

        /*
        this function makes the window movable
        input: sender and event
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
        this function goes to the statistics menu
        input: sender and event
        output: none
        */
        private void statisticsMenu_Click(object sender, RoutedEventArgs e)
        {
            StatisticsMenu newStatsWindow = new StatisticsMenu();
            this.Close();
            newStatsWindow.Show();
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

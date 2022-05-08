using MaterialDesignThemes.Wpf;
using System;
using System.Collections.Generic;
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
    public partial class statisticsWindow : Window
    {
        const int CorrectAnswersIndex = 2;
        const int totalAnswersIndex = 3;
        const int amountOfGamesIndex = 1;
        const int avgAnswerTimeIndex = 4;
        public statisticsWindow()
        {
            InitializeComponent();
            string request = Convert.ToString(Communicator.GET_PERSONAL_STATS_REQUEST) + "\0\0\0\0";
            Communicator.sendData(request);
            Communicator.GetMessageTypeCode();
            string response = Communicator.GetStringPartFromSocket(Communicator.getSizePart(checkServerResponse.MAX_DATA_SIZE));
            getPersonalStatsResponse stats = desirializer.deserializeRequest<getPersonalStatsResponse>(response);
            if(stats.status == (int)checkServerResponse.Status.STATUS_DB_PROBLEM)
            {
                statisticsDataText.Foreground = System.Windows.Media.Brushes.Red;
                statisticsDataText.Text = "error occured trying to receive data from the dataBase.";
            }
            else
            {
                Title.Text = stats.statistics[0] + " Statistics";
                avgTimeForAnswer.Text = avgTimeForAnswer.Text + "      " + stats.statistics[avgAnswerTimeIndex];
                amountOfWrongAnswers.Text = amountOfWrongAnswers.Text + "      " + Convert.ToString(int.Parse(stats.statistics[totalAnswersIndex]) - int.Parse(stats.statistics[CorrectAnswersIndex]));
                amountOfCorrectAnswers.Text = amountOfCorrectAnswers.Text + "      " + stats.statistics[CorrectAnswersIndex];
                amountOfGames.Text = amountOfGames.Text + "      " + stats.statistics[amountOfGamesIndex];
            }
        }
        public bool IsDarkTheme { get; set; }
        private readonly PaletteHelper paletteHelper = new PaletteHelper();
        private void toggleTheme(object sender, RoutedEventArgs e)
        {
            ITheme theme = paletteHelper.GetTheme();

            if (IsDarkTheme = theme.GetBaseTheme() == BaseTheme.Dark)
            {
                IsDarkTheme = false;
                theme.SetBaseTheme(Theme.Light);
            }
            else
            {
                IsDarkTheme = true;
                theme.SetBaseTheme(Theme.Dark);
            }
            paletteHelper.SetTheme(theme);
        }

        private void exitApp(object sender, RoutedEventArgs e)
        {
            Communicator.logOut();
        }

        protected override void OnMouseLeftButtonDown(MouseButtonEventArgs e)
        {
            base.OnMouseLeftButtonDown(e);
            DragMove();
        }

        private void menuButton_Click(object sender, RoutedEventArgs e)
        {
            MainMenu newLoginWindow = new MainMenu();
            this.Close();
            newLoginWindow.Show();
        }
    }
}

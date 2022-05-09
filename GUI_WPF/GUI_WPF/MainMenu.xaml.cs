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
using MaterialDesignThemes.Wpf;

namespace GUI_WPF
{
    /// <summary>
    /// Interaction logic for MainMenu.xaml
    /// </summary>
    public partial class MainMenu : Window
    {
        public MainMenu()
        {
            InitializeComponent();
        }
        private void toggleTheme(object sender, RoutedEventArgs e)
        {
            sharedFunctionsBetweenWindows.toggleTheme(sender, e);
        }
        private void exitApp(object sender, RoutedEventArgs e)
        {
            Communicator.logOut();
        }
        private void createRoomButton_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("not implemented yet");
        }
        private void joinRoomButton_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("not implemented yet");
        }
        private void statisticsButton_Click(object sender, RoutedEventArgs e)
        {
            StatisticsMenu newStatsWindow = new StatisticsMenu();
            this.Close();
            newStatsWindow.Show();
        }
    }
}

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
using MaterialDesignThemes.Wpf;

namespace GUI_WPF
{
    /// <summary>
    /// Interaction logic for MainMenu.xaml
    /// </summary>
    public partial class MainMenu : Window
    {
        /*
        this function intialize the window
        input: none
        output: none
        */
        public MainMenu()
        {
            InitializeComponent();
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
        this function goes to the create button window
        input: sender and event
        output: none
        */
        private void createRoomButton_Click(object sender, RoutedEventArgs e)
        {
            CreateRoomWindow newStatsWindow = new CreateRoomWindow();
            this.Close();
            newStatsWindow.Show();
        }

        /*
        this function goes to the join room window
        input: sender and event
        output: none
        */
        private void joinRoomButton_Click(object sender, RoutedEventArgs e)
        {
            RoomListWindow newRoomListWindow = new RoomListWindow();
            this.Close();
            newRoomListWindow.Show();
        }

        /*
        this function goes to the statistics window
        input: sender and event
        output: none
        */
        private void statisticsButton_Click(object sender, RoutedEventArgs e)
        {
            StatisticsMenu newStatsWindow = new StatisticsMenu();
            this.Close();
            newStatsWindow.Show();
        }
    }
}

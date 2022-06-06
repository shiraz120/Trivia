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
        public MainMenu()
        {
            InitializeComponent();
        }
        public void HandleClosingWindow(object sender, CancelEventArgs e)
        {
            Communicator.logOut();
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
        public void HandleClosingWindow(object sender, RoutedEventArgs e)
        {
            Communicator.logOut();
            Closing -= HandleClosingWindow;
        }
        private void createRoomButton_Click(object sender, RoutedEventArgs e)
        {
            Closing -= HandleClosingWindow;
            CreateRoomWindow newStatsWindow = new CreateRoomWindow();
            this.Close();
            newStatsWindow.Show();
        }
        private void joinRoomButton_Click(object sender, RoutedEventArgs e)
        {
            Closing -= HandleClosingWindow;
            RoomListWindow newRoomListWindow = new RoomListWindow();
            this.Close();
            newRoomListWindow.Show();
        }
        private void statisticsButton_Click(object sender, RoutedEventArgs e)
        {
            Closing -= HandleClosingWindow;
            StatisticsMenu newStatsWindow = new StatisticsMenu();
            this.Close();
            newStatsWindow.Show();
        }
    }
}

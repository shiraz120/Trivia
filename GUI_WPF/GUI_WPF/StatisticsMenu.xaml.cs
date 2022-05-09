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
    /// Interaction logic for StatisticsMenu.xaml
    /// </summary>
    public partial class StatisticsMenu : Window
    {
        public StatisticsMenu()
        {
            InitializeComponent();
        }
        private void toggleTheme(object sender, RoutedEventArgs e)
        {
            sharedFunctionsBetweenWindows.toggleTheme(sender, e);
        }
        private void menu_Click(object sender, RoutedEventArgs e)
        {
            sharedFunctionsBetweenWindows.moveToMenu(this);
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

        private void myStats_Click(object sender, RoutedEventArgs e)
        {
            MyStatisticsWindow newStatsWindow = new MyStatisticsWindow();
            this.Close();
            newStatsWindow.Show();
        }

        private void highScore_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("not implemented yet");
        }

    }
}

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
    /// Interaction logic for WaitingWindow.xaml
    /// </summary>
    public partial class WaitingWindow : Window
    {
        public WaitingWindow()
        {
            InitializeComponent();
        }
        public void HandleClosingWindow(object sender, CancelEventArgs e)
        {
            Communicator.logOut();
        }
        public void HandleClosingWindow(object sender, RoutedEventArgs e)
        {
            Communicator.logOut();
            Closing -= HandleClosingWindow;
        }
        private void toggleTheme(object sender, RoutedEventArgs e)
        {
            sharedFunctionsBetweenWindows.toggleTheme(sender, e);
        }
    }
}

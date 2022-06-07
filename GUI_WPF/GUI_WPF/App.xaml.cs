using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;

namespace GUI_WPF
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        /*
        this function starts the first window and the commucator
        input: sender and event
        output: none
        */
        private void Application_Startup(object sender, StartupEventArgs e) // added this function to run StartCommunication only once in the program before any window open
        {
            Communicator.StartCommunication();
            var mainWindow = new MainWindow();
            mainWindow.Show();
        }
    }
}

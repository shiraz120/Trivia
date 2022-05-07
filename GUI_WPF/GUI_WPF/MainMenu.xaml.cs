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
            string request = Convert.ToString(Communicator.SIGNOUT_REQUEST) + "\0\0\0\0";
            Communicator.sendData(request);
            int status = checkServerResponse.checkIfLogoutSucceeded();
            if (status == 4)
                Application.Current.Shutdown();
            else
                MessageBox.Show("couldnt logout, the specified user doesnt login.");
        }
        private void createRoomButton_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("not implemented yet hehehe");
        }
        private void joinRoomButton_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("not implemented yet hehehe");
        }
        private void statisticsButton_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("not implemented yet hehehe");
        }

    }
}

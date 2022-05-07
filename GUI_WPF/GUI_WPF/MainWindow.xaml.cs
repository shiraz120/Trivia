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
using System.Windows.Navigation;
using System.Windows.Shapes;
using MaterialDesignThemes.Wpf;

namespace GUI_WPF
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }
        public bool IsDarkTheme { get; set; }
        private readonly PaletteHelper paletteHelper = new PaletteHelper();
        private void toggleTheme(object sender, RoutedEventArgs e)
        {
            ITheme theme = paletteHelper.GetTheme();

            if(IsDarkTheme = theme.GetBaseTheme() == BaseTheme.Dark)
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
            Application.Current.Shutdown();
        }

        protected override void OnMouseLeftButtonDown(MouseButtonEventArgs e)
        {
            base.OnMouseLeftButtonDown(e);
            DragMove();
        }

        private void loginButton_Click(object sender, RoutedEventArgs e)
        {
            loginRequest login = new loginRequest
            {
                username = txtUsername.Text,
                password = txtPassword.Password
            };
            string loginAsString = serializer.serializeResponse<loginRequest>(login, Communicator.LOGIN_REQUEST);
            Communicator.sendData(loginAsString);
            string loginResponse = checkServerResponse.checkIfLoginSucceded();
            loginDataText.Text = loginResponse;
            if(loginResponse == "login succeeded!")
            {
                MainMenu replacedWindow = new MainMenu();
                this.Close();
                replacedWindow.ShowDialog();
            }
            else
                loginDataText.Foreground = System.Windows.Media.Brushes.Red;
        }

        private void signupButton_Click(object sender, RoutedEventArgs e)
        {
            Signup replacedWindow = new Signup();
            this.Close();
            replacedWindow.ShowDialog();
        }
    }
}

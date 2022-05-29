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
        private void toggleTheme(object sender, RoutedEventArgs e)
        {
            sharedFunctionsBetweenWindows.toggleTheme(sender, e);
        }
        protected override void OnMouseLeftButtonDown(MouseButtonEventArgs e)
        {
            base.OnMouseLeftButtonDown(e);
            DragMove();
        }
        private void exitApp(object sender, RoutedEventArgs e)
        {
            Application.Current.Shutdown();
        }
        private void loginButton_Click(object sender, RoutedEventArgs e)
        {
            if(string.IsNullOrWhiteSpace(txtUsername.Text))
            {
                loginDataText.Text = "username filed cannot be empty.";
            }
            else if (txtPassword.Password.Length < sharedFunctionsBetweenWindows.MIN_PASSWORD_LENGTH)
            {
                loginDataText.Text = "password filed must contain at least " + Convert.ToString(sharedFunctionsBetweenWindows.MIN_PASSWORD_LENGTH) + " characters.";
            }
            else
            {
                loginRequest login = new loginRequest
                {
                    username = txtUsername.Text,
                    password = txtPassword.Password
                };
                Communicator.sendData(serializer.serializeResponse<loginRequest>(login, Communicator.LOGIN_REQUEST));
                string loginResponse = checkServerResponse.checkIfLoginSucceded();
                loginDataText.Text = loginResponse;
                if(loginResponse == checkServerResponse.LOGIN_SUCCEEDED)
                {
                    MainMenu replacedWindow = new MainMenu();
                    this.Close();
                    replacedWindow.ShowDialog();
                    loginDataText.Foreground = System.Windows.Media.Brushes.Green;
                }
            }
        }

        private void signupButton_Click(object sender, RoutedEventArgs e)
        {
            Signup replacedWindow = new Signup();
            this.Close();
            replacedWindow.ShowDialog();
        }
        
        private void txtUsername_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (!string.IsNullOrWhiteSpace(txtUsername.Text))
                loginDataText.Text = "";
            else
                loginDataText.Text = sharedFunctionsBetweenWindows.INVALID_NAME;
        }

        private void txtPassword_PasswordChanged(object sender, RoutedEventArgs e)
        {
            if(!string.IsNullOrWhiteSpace(txtPassword.Password))
                loginDataText.Text = "";
            else
                loginDataText.Text = sharedFunctionsBetweenWindows.INVALID_PASSWORD;
        }
    }
}

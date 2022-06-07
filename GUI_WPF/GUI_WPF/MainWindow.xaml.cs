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
        /*
        this function initalize the window
        input: none
        output: none
        */
        public MainWindow()
        {
            InitializeComponent();
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
        this function exits the app
        input: sender and event
        output: none
        */
        private void exitApp(object sender, RoutedEventArgs e)
        {
            Application.Current.Shutdown();
        }

        /*
        this function logs in
        input: sender and event
        output: none
        */
        private void loginButton_Click(object sender, RoutedEventArgs e)
        {
            if(string.IsNullOrWhiteSpace(txtUsername.Text)) //if the username empty
            {
                loginDataText.Text = "username filed cannot be empty.";
            }
            else if (txtPassword.Password.Length < sharedFunctionsBetweenWindows.MIN_PASSWORD_LENGTH) // password is to short
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
                Communicator.sendData(serializer.serializeResponse<loginRequest>(login, Communicator.LOGIN_REQUEST));  //sends the login request
                loginDataText.Text = checkServerResponse.checkIfErrorResponse();
                if (loginDataText.Text == "")
                {
                    string loginCheck = checkServerResponse.checkIfLoginSucceded();
                    if (checkServerResponse.LOGIN_SUCCEEDED == loginCheck)
                    {
                        MainMenu replacedWindow = new MainMenu();
                        this.Close();
                        replacedWindow.ShowDialog();
                    }
                    else
                        loginDataText.Text = loginCheck;
                }
            }
        }

        /*
        this function goes to the sign up window
        input: sender and event
        output: none
        */
        private void signupButton_Click(object sender, RoutedEventArgs e)
        {
            Signup replacedWindow = new Signup();
            this.Close();
            replacedWindow.ShowDialog();
        }

        /*
        this function changes if there is an error with the username
        input: sender and event
        output: none
        */
        private void txtUsername_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (!string.IsNullOrWhiteSpace(txtUsername.Text))
                loginDataText.Text = "";
            else
                loginDataText.Text = sharedFunctionsBetweenWindows.INVALID_NAME;
        }

        /*
        this function changes if there is an error with the password
        input: sender and event
        output: none
        */
        private void txtPassword_PasswordChanged(object sender, RoutedEventArgs e)
        {
            if(!string.IsNullOrWhiteSpace(txtPassword.Password))
                loginDataText.Text = "";
            else
                loginDataText.Text = sharedFunctionsBetweenWindows.INVALID_PASSWORD;
        }
    }
}

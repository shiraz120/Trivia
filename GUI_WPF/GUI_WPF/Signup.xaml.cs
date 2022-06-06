using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.ComponentModel;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using MaterialDesignThemes.Wpf;

namespace GUI_WPF
{
    /// <summary>
    /// Interaction logic for Signup.xaml
    /// </summary>
    public partial class Signup : Window
    {
        private readonly string INVALID_EMAIL = "email filed cannot be empty.";
        public Signup()
        {
            InitializeComponent();
        }
        private void toggleTheme(object sender, RoutedEventArgs e)
        {
            sharedFunctionsBetweenWindows.toggleTheme(sender, e);
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
            MainWindow newLoginWindow = new MainWindow();
            this.Close();
            newLoginWindow.Show();
        }

        private void signupButton_Click(object sender, RoutedEventArgs e)
        {
            signupDataText.Foreground = System.Windows.Media.Brushes.Red;
            if (string.IsNullOrWhiteSpace(txtUsername.Text))
            {
                signupDataText.Text = sharedFunctionsBetweenWindows.INVALID_NAME;
            }
            else if (txtPassword.Password.Length < sharedFunctionsBetweenWindows.MIN_PASSWORD_LENGTH)
            {
                signupDataText.Text = sharedFunctionsBetweenWindows.INVALID_PASSWORD;
            }
            else if (string.IsNullOrWhiteSpace(txtEmail.Text))
            {
                signupDataText.Text = INVALID_EMAIL;
            }
            else
            {
                SignupRequest signup = new SignupRequest
                {
                    email = txtEmail.Text,
                    username = txtUsername.Text,
                    password = txtPassword.Password
                };
                Communicator.sendData(serializer.serializeResponse<SignupRequest>(signup, Communicator.SIGNUP_REQUEST));
                signupDataText.Text = checkServerResponse.checkIfErrorResponse();
                if (signupDataText.Text == "")
                {
                    signupDataText.Text = checkServerResponse.checkIfSigupSucceded();
                    if(signupDataText.Text == checkServerResponse.SIGNUP_SUCCEEDED)
                        signupDataText.Foreground = System.Windows.Media.Brushes.Green;
                }
            }
        }

        private void txtUsername_TextChanged(object sender, TextChangedEventArgs e)
        {
            if(!string.IsNullOrWhiteSpace(txtUsername.Text))
                signupDataText.Text = "";
            else
                signupDataText.Text = sharedFunctionsBetweenWindows.INVALID_NAME;
        }
        
        private void txtPassword_PasswordChanged(object sender, RoutedEventArgs e)
        {
            if (txtPassword.Password.Length < sharedFunctionsBetweenWindows.MIN_PASSWORD_LENGTH)
                signupDataText.Text = "";
            else
                signupDataText.Text = sharedFunctionsBetweenWindows.INVALID_PASSWORD;
        }

        private void txtEmail_TextChanged(object sender, TextChangedEventArgs e)
        {
            if(!string.IsNullOrWhiteSpace(txtEmail.Text))
                signupDataText.Text = "";
            else
                signupDataText.Text = INVALID_EMAIL;
        }
    }
}

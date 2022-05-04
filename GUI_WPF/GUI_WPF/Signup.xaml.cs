﻿using System;
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

namespace GUI_WPF
{
    /// <summary>
    /// Interaction logic for Signup.xaml
    /// </summary>
    public partial class Signup : Window
    {
        public Signup()
        {
            InitializeComponent();
        }
        public bool IsDarkTheme { get; set; }

        //private readonly PaletteHelper paletteHelper = new PaletteHelper();
        private void toggleTheme(object sender, RoutedEventArgs e)
        {
            //ITheme theme = paletteHelper.GetTheme();
            //
            //if (IsDarkTheme = theme.GetBaseTheme() == BaseTheme.Dark)
            //{
            //    IsDarkTheme = false;
            //    theme.SetBaseTheme(Theme.Light);
            //}
            //else
            //{
            //    IsDarkTheme = true;
            //    theme.SetBaseTheme(Theme.Dark);
            //}
            //paletteHelper.SetTheme(theme);
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

        }

        private void txtUsername_TextChanged(object sender, TextChangedEventArgs e)
        {
        }
    }
}

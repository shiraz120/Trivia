using MaterialDesignThemes.Wpf;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace GUI_WPF
{
    public class sharedFunctionsBetweenWindows
    {
        static public bool IsDarkTheme { get; set; }
        static public readonly int MIN_PASSWORD_LENGTH = 5;
        static public readonly string INVALID_NAME = "username filed cant be empty.";
        static public readonly string INVALID_PASSWORD = "password filed must contain at least " + Convert.ToString(sharedFunctionsBetweenWindows.MIN_PASSWORD_LENGTH) + " characters.";

        static private readonly PaletteHelper paletteHelper = new PaletteHelper();
        static public void moveToMenu(Window pointerToWindow)
        {
            MainMenu newStatsWindow = new MainMenu();
            pointerToWindow.Close();
            newStatsWindow.Show();
        }
        static public void toggleTheme(object sender, RoutedEventArgs e)
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
    }
}

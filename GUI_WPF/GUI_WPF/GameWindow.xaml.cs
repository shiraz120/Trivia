using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading;
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
    /// Interaction logic for GameWindow.xaml
    /// </summary>
    public partial class GameWindow : Window
    {
        public GameWindow(Window windowToClose)
        {
            InitializeComponent();
            windowToClose.Close();
            Communicator.sendData(Communicator.GET_QUESTION_REQUEST + "\0\0\0\0");
            string error = checkServerResponse.checkIfErrorResponse();
            if (error == "")
            {
                getQuestionResponse getQuestionResponse = desirializer.deserializeRequest<getQuestionResponse>(Communicator.GetStringPartFromSocket(Communicator.getSizePart(checkServerResponse.MAX_DATA_SIZE)));
                if(getQuestionResponse.status == 1)
                {
                    questionText.Text = getQuestionResponse.question;
                    answerOne.Content = getQuestionResponse.answers[0];
                    answerTwo.Content = getQuestionResponse.answers[1];
                    answerThree.Content = getQuestionResponse.answers[2];
                    answerFour.Content = getQuestionResponse.answers[3];
                    this.Show();
                }
                else
                {
                    ScoreboardWindow newScoreWindow = new ScoreboardWindow();
                    this.Close();
                    newScoreWindow.Show();
                }
            }
            else
            {
                MessageBox.Show(error);
                Application.Current.Shutdown();
            }
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
        this function toggles the theme
        input: sender and event
        output: none
        */
        private void toggleTheme(object sender, RoutedEventArgs e)
        {
            sharedFunctionsBetweenWindows.toggleTheme(sender, e);
        }

        /*
        this function leaves the game
        input: none
        output: none
        */
        private void leaveGameButton_Click(object sender, RoutedEventArgs e)
        {
            Communicator.sendData(Convert.ToString(Communicator.LEAVE_GAME_REQUEST) + "\0\0\0\0");
            string error = checkServerResponse.checkIfErrorResponse();
            if (error == "")
            {
                leaveGameResponse stats = desirializer.deserializeRequest<leaveGameResponse>(Communicator.GetStringPartFromSocket(Communicator.getSizePart(checkServerResponse.MAX_DATA_SIZE)));
                RoomListWindow newListWindow = new RoomListWindow();
                this.Close();
                newListWindow.Show();
            }
        }

        private void handleAnswerClick(int index, Button btn)
        {
            submitAnswerRequest request = new submitAnswerRequest();
            request.answerId = index;
            Communicator.sendData(serializer.serializeResponse<submitAnswerRequest>(request, Communicator.SUBMIT_ANSWER_REQUEST));
            string error = checkServerResponse.checkIfErrorResponse();
            if(error == "")
            {
                submitAnswerResponse response = desirializer.deserializeRequest<submitAnswerResponse>(Communicator.GetStringPartFromSocket(Communicator.getSizePart(checkServerResponse.MAX_DATA_SIZE)));
                if (response.correctAnswerId != index)
                    btn.Background = Brushes.Red;
                if (response.correctAnswerId == 0)
                    answerOne.Background = Brushes.Green;
                else if(response.correctAnswerId == 1)
                    answerTwo.Background = Brushes.Green;
                else if(response.correctAnswerId == 2)
                    answerThree.Background = Brushes.Green;
                else if(response.correctAnswerId == 3)
                    answerFour.Background = Brushes.Green;
                GameWindow newQuestion = new GameWindow(this);
            }
            else
            {
                MessageBox.Show(error);
                Application.Current.Shutdown();
            }
        }
        
        /*
        this function closes the thread and logs out of the communicator
        input: sender and event
        output: none
        */
        private void exitBtnClick(object sender, RoutedEventArgs e)
        {
            Application.Current.Shutdown();
        }

        private void answerThree_Click(object sender, RoutedEventArgs e)
        {
            handleAnswerClick(2, answerThree);
        }

        private void answerTwo_Click(object sender, RoutedEventArgs e)
        {
            handleAnswerClick(1, answerTwo);
        }

        private void answerOne_Click(object sender, RoutedEventArgs e)
        {
            handleAnswerClick(0, answerOne);
        }

        private void answerFour_Click(object sender, RoutedEventArgs e)
        {
            handleAnswerClick(3, answerFour);
        }
    }
}

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
        /*
        this function loads the game window, opens a thread that will keep track of the time and will go to the next question if there is not enough time
        input: none
        output: none
        */
        public GameWindow()
        {
            InitializeComponent();
            Button[] answersBtn = { answerOne, answerTwo, answerThree, answerFour };
            if (sharedFunctionsBetweenWindows.amountOfQuestions < 0)
            {
                this.Close();
                ScoreboardWindow scoreboard = new ScoreboardWindow();
                scoreboard.Show();
            }
            Thread time = new Thread(timer);
            time.Start();
            questionLeftTbox.Text = "Question left: " + sharedFunctionsBetweenWindows.amountOfQuestions;
            correctCounterTbox.Text = "Correct answers: " + sharedFunctionsBetweenWindows.correctAnswers;
            string request = Convert.ToString(Communicator.GET_QUESTION_REQUEST) + "\0\0\0\0";
            Communicator.sendData(request);
            string error = checkServerResponse.checkIfErrorResponse();
            if (error != "")
            {
                MessageBox.Show(error);
                Application.Current.Shutdown();
            }
            string response = Communicator.GetStringPartFromSocket(Communicator.getSizePart(checkServerResponse.MAX_DATA_SIZE));
            getQuestionResponse question = desirializer.deserializeRequest<getQuestionResponse>(response);
            questionTbox.Text = question.question;
            for (int i = 0; i < 4; i++)
            {
                if (question.answers.Count > i)
                    answersBtn[i].Content = question.answers[i];
                else
                    answersBtn[i].Content = "";
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
        this function closes the thread and logs out of the communicator
        input: sender and event
        output: none
        */
        private void exitBtnClick(object sender, RoutedEventArgs e)
        {
            Application.Current.Shutdown();
        }

        /*
        this function sends the answer with id 0 and opens a new question
        input: sender and event
        output: none
        */
        private void answerOne_Click(object sender, RoutedEventArgs e)
        {
            if (answerOne.Content.ToString() == "")
            {
                MessageBox.Show("You have to choose a valid answer");
                return;
            }
            sendAnswer(0);
        }

        /*
        this function sends the answer with id 1 and opens a new question
        input: sender and event
        output: none
        */
        private void answerTwo_Click(object sender, RoutedEventArgs e)
        {
            if (answerTwo.Content.ToString() == "")
            {
                MessageBox.Show("You have to choose a valid answer");
                return;
            }
            sendAnswer(1);
        }

        /*
        this function sends the answer with id 2 and opens a new question
        input: sender and event
        output: none
        */
        private void answerThree_Click(object sender, RoutedEventArgs e)
        {
            if (answerThree.Content.ToString() == "")
            {
                MessageBox.Show("You have to choose a valid answer");
                return;
            }
            sendAnswer(2);
        }

        /*
        this function sends the answer with id 3 and opens a new question
        input: sender and event
        output: none
        */
        private void answerFour_Click(object sender, RoutedEventArgs e)
        {
            if (answerFour.Content.ToString() == "")
            {
                MessageBox.Show("You have to choose a valid answer");
                return;
            }
            sendAnswer(3);
        }

        /*
        this function keeps track on the time and if the user ran out of time it sends the answer with -1 id and opens a new question
        input: none
        output: none
        */
        private void timer()
        {
            int tempTime = sharedFunctionsBetweenWindows.timeLeft;
            while (tempTime > 0)
            {
                timeLeftTbox.Dispatcher.Invoke(() => { timeLeftTbox.Text = "Time left: " + tempTime + " sec"; });
                Thread.Sleep(1000);
                tempTime--;
            }
            sendAnswer(-1);
        }

        /*
        this function sends the answer with the correspondent id and opens a new question
        input: id
        output: none
        */
        private void sendAnswer(int id)
        {
            submitAnswerRequest request = new submitAnswerRequest { answerId = id };
            Communicator.sendData(serializer.serializeResponse<submitAnswerRequest>(request, Communicator.SUBMIT_ANSWER_REQUEST));
            string error = checkServerResponse.checkIfErrorResponse();
            if (error != "")
            {
                MessageBox.Show(error);
                Application.Current.Shutdown();
            }
            submitAnswerResponse response = desirializer.deserializeRequest<submitAnswerResponse>(Communicator.GetStringPartFromSocket(Communicator.getSizePart(checkServerResponse.MAX_DATA_SIZE)));
            if (response.correctAnswerId == id)
            {
                sharedFunctionsBetweenWindows.correctAnswers++;
            }
            sharedFunctionsBetweenWindows.amountOfQuestions--;
            GameWindow newQuestionWindow = new GameWindow();
            this.Close();
            newQuestionWindow.Show();
        }
    }
}

#include "Question.h"

/*
this function will create an empty Question obejct
input: none
output: none
*/
Question::Question()
{
}

/*
this function will create a Question obejct
input: question, correctAnswer, firstIncorrect, secondIncorrect, thirdIncorrect
output: none
*/
Question::Question(const string question, const string correctAnswer, const string firstIncorrect, const string secondIncorrect, const string thirdIncorrect) : m_question(question), m_correctAnswer(correctAnswer)
{
	vector<string> temp = { firstIncorrect, secondIncorrect, thirdIncorrect };
	int amountOfAnswers = MAX - std::count(temp.begin(), temp.end(), "");
	int counter = 0;
	m_possibleAnswers.resize(MAX + 1);
	m_possibleAnswers[rand() % (amountOfAnswers - MIN + 1) + MIN] = correctAnswer;
	for (int i = 0; i < m_possibleAnswers.size(); i++)
	{
		if (m_possibleAnswers[i] != correctAnswer)
		{
			m_possibleAnswers[i] = temp[counter];
			counter++;
		}
	}
}

/*
this function will remove a Question object
input: none
output: none
*/
Question::~Question()
{
}

/*
this function will return the object m_question
input: none
output: m_question
*/
string Question::getQuestion() const
{
	return m_question;
}

/*
this function will return the object m_possibleAnswers
input: none
output: m_possibleAnswers
*/
vector<string> Question::getPossibleAnswers() const
{
	return m_possibleAnswers;
}

/*
this function will return the object m_correctAnswer
input: none
output: m_correctAnswer
*/
string Question::getCorrentAnswer() const
{
	return m_correctAnswer;
}

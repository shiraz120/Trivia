#include "Question.h"

Question::Question()
{
}

Question::Question(const string question, const string correctAnswer, const string firstIncorrect, const string secondIncorrect, const string thirdIncorrect) : m_question(question), m_correctAnswer(correctAnswer)
{
	vector<string> temp = { firstIncorrect, secondIncorrect, thirdIncorrect };
	int amountOfAnswers = MAX - std::count(temp.begin(), temp.end(), "");
	int counter = 0;
	m_possibleAnswers.resize(amountOfAnswers + 1);
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

Question::~Question()
{
}

string Question::getQuestion() const
{
	return m_question;
}

vector<string> Question::getPossibleAnswers() const
{
	return m_possibleAnswers;
}

string Question::getCorrentAnswer() const
{
	return m_correctAnswer;
}

Question& Question::operator=(const Question& other)
{
	if (this != &other)
	{
		this->m_question = other.m_question;
		this->m_correctAnswer = other.m_correctAnswer;
		for (auto it : other.getPossibleAnswers())
			this->m_possibleAnswers.push_back(it);
	}
	return *this;
}

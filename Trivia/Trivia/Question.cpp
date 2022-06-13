#include "Question.h"

Question::Question()
{
}

Question::Question(const string question, const string correctAnswer, const string firstIncorrect, const string secondIncorrect, const string thirdIncorrect) : m_question(question), m_correctAnswer(correctAnswer)
{
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

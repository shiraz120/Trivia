#pragma once
#include <string>
#include <vector>
#include <cstdlib>
#define MIN 0
#define MAX 3

using std::vector;
using std::string;
class Question
{
public:
	Question();
	Question(const string question, const string correctAnswer, const string firstIncorrect, const string secondIncorrect, const string thirdIncorrect);
	~Question();
	string getQuestion() const;
	vector<string> getPossibleAnswers() const;
	string getCorrentAnswer() const;
	Question& operator=(const Question& other);

private:
	string m_correctAnswer;
	string m_question;
	vector<string> m_possibleAnswers;
};
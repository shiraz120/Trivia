#pragma once
#include <string>
#include <vector>

#define QUESTION "question"
#define CORRECT_ANSWER "correctAnswer"
#define FIRST_INCORRECT_ANSWER "firstIncorrectAnswer"
#define SECOND_INCORRECT_ANSWER "secondIncorrectAnswer"
#define THIRD_INCORRECT_ANSWER "thirdIncorrectAnswer"

struct questionMetaData
{
	std::string question;
	std::string correctAnswer;
	std::vector<std::string> inncorrectAnswers;
};

struct results
{
	std::vector<questionMetaData> resultsFromJson;
};
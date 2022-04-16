#include "convertJsonToHelpers.h"

void from_json(const json& jsonResults, results& resultsJson)
{
	jsonResults.at("results").get_to(resultsJson.resultsFromJson);
}

void from_json(const json& jsonQuestionData, questionMetaData& questionDataFromJson)
{
	jsonQuestionData.at("question").get_to(questionDataFromJson.question);
	jsonQuestionData.at("correct_answer").get_to(questionDataFromJson.correctAnswer);
	jsonQuestionData.at("incorrect_answers").get_to(questionDataFromJson.inncorrectAnswers);
}

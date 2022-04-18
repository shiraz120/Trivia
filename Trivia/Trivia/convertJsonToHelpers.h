#pragma once
#include "dataBaseStructsHelpers.h"
#include "json.hpp"
using nlohmann::json;
void from_json(const json& jsonResults, results& resultsJson);
void from_json(const json& jsonQuestionData, questionMetaData& questionDataFromJson);
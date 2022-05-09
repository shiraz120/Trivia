#include "dataBase.h"

/*
this function will create a SqliteDatabase object and init the data base
input: none
output: none
*/
SqliteDatabase::SqliteDatabase() : _db(nullptr)
{
	std::string name = DB_NAME;
	int file_exist = _access(name.c_str(), 0);
	int res = sqlite3_open(DB_NAME, &_db);
	if (res != SQLITE_OK)
	{
		_db = nullptr;
	}
	try {
		if (file_exist != 0)
		{
			sendQuery("create table if not exists clients(user_name TEXT PRIMARY KEY NOT NULL, password TEXT NOT NULL, email TEXT NOT NULL);");
			sendQuery("create table if not exists statistics(user_name TEXT NOT NULL, correct_answers INTEGER NOT NULL, amount_of_games INTEGER NOT NULL, incorrect_answers INTEGER NOT NULL, avarage_answer_time REAL NOT NULL, FOREIGN KEY(user_name) REFERENCES clients(user_name));");
		}
		sendQuery("drop table if exists questions; create table if not exists questions(id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, question TEXT NOT NULL, correctAnswer TEXT NOT NULL, firstIncorrectAnswer TEXT NOT NULL, secondIncorrectAnswer TEXT NOT NULL, thirdIncorrectAnswer TEXT NOT NULL);");
		initQuestionsTable();
	}
	catch (dataBaseException& e)
	{
		std::cerr << e.what() << std::endl;
		exit(1);
	}
}

/*
this function will delete SqliteDatabase object and close the data base
input: none
output: none
*/
SqliteDatabase::~SqliteDatabase()
{
	sqlite3_close(_db);
	_db = nullptr;
}

/*
this function will check if a user already exists in the data base
input: username
output: bool - if a user already exists in the data base
*/
bool SqliteDatabase::doesUserExist(const string username)
{
	float count;
	sendQuery("SELECT COUNT(*) FROM clients where user_name == '" + username + "';", callbackCounter, &count);
	if (count > 0)
		return true;
	return false;
}

/*
this function will check if a password matches the user
input: username, password
output: bool - if a password matches the user
*/
bool SqliteDatabase::doesPasswordMatch(const string username, const string password)
{
	float count;
	sendQuery("SELECT COUNT(*) FROM clients where password == '" + password + "' AND user_name == '" + username + "';", callbackCounter, &count);
	if (count > 0)
		return true;
	return false;
}

/*
this function will add a new user to the data base
input: username, password, email
output: none
*/
void SqliteDatabase::addNewUser(const string username, const string password, const string email)
{
	if (!doesUserExist(username)) 
	{
		sendQuery("insert into clients(user_name, password, email) values ('" + username + "', '" + password + "', '" + email + "');");
		sendQuery("insert into statistics(user_name, correct_answers, incorrect_answers, amount_of_games, avarage_answer_time) values ('" + username + "', 0, 0, 0, 0);");
	}
}

/*
this function will return all the questions and answers
input: int 
output: all the questions and answers
*/
std::list<questionMetaData> SqliteDatabase::getQuestions(const int i) // will replace questionMetaData with Question on v4.0.0
{
	std::list<questionMetaData> questionsData;
	sendQuery("select * from questions limit " + std::to_string(i) + ";", callBackQuestion, &questionsData);
	return questionsData;
}

/*
this function will return the requested user amount of games played
input: username
output: the user amount of games played
*/
int SqliteDatabase::getNumOfPlayerGames(const string username)
{
	float numOfGames;
	sendQuery("select amount_of_games from statistics where user_name == '" + username + "';", callbackCounter, &numOfGames);
	return (int)numOfGames;
}

/*
this function will return the requested user amount of answers
input: username
output: the user amount of answers
*/
int SqliteDatabase::getNumOfTotalAnswers(const string username)
{
	float numOfIncorrectAnswers;
	float numOfCorrectAnswers;
	sendQuery("select incorrect_answers from statistics where user_name == '" + username + "';", callbackCounter, &numOfIncorrectAnswers);
	sendQuery("select correct_answers from statistics where user_name == '" + username + "';", callbackCounter, &numOfCorrectAnswers);
	return (int)(numOfIncorrectAnswers + numOfCorrectAnswers);
}

/*
this function will return the requested user amount of correct answers
input: username
output: the user amount of correct answers
*/
int SqliteDatabase::getNumOfCorrectAnswers(const string username)
{
	float numOfCorrectAnswers;
	sendQuery("select correct_answers from statistics where user_name == '" + username + "';", callbackCounter, &numOfCorrectAnswers);
	return (int)numOfCorrectAnswers;
}

/*
this function will return the requested user average answer time
input: username
output: the avarage answer time
*/
float SqliteDatabase::getPlayerAverageAnswerTime(const string username)
{
	float avgTime;
	sendQuery("select avarage_answer_time from statistics where user_name == '" + username + "';", callbackCounter, &avgTime);
	return avgTime;
}


/*
this function returns usernames with stats
input: none
output: usernames with stats
*/
std::map<string, std::pair<int, float>> SqliteDatabase::getUsersStatsForScore()
{
	std::map<string, std::pair<int, float>> users;
	sendQuery("select user_name, correct_answers, avarage_answer_time from statistics;", callbackStats, &users);
	return users;
}


/*
this function will receive a query and send it, return true if the query succeeded and false if not, the fuunction will
also use a template for diffenet list types
input: query, callback function, print function, list
output: bool - return true if the query succeeded and false if not
*/
template <class T> void SqliteDatabase::sendQuery(const std::string query, int(callBack)(void* data, int argc, char** argv, char** azColName), std::list<T>* list)
{
	char* error = nullptr;
	int res = sqlite3_exec(_db, query.c_str(), callBack, list, &error);
	if (res != SQLITE_OK)
		throw dataBaseException(error);
}

/*
this function will add the random questions from the json file into the data base
input: none
output: none
*/
void SqliteDatabase::initQuestionsTable()
{
	createJsonFile();
	std::ifstream file(FILE_NAME);
	std::string line = "";
	std::string data = "";
	do {
		std::getline(file, line);
		data += line;
	} while (file.peek() != EOF);
	file.close();
	json jsonFromData = json::parse(data);
	results qs = jsonFromData;
	data = "";
	for (auto it = qs.resultsFromJson.begin(); it != qs.resultsFromJson.end(); it++)
	{
		if(it->inncorrectAnswers.size() == 3)
			sendQuery("INSERT INTO questions (question, correctAnswer, firstIncorrectAnswer, secondIncorrectAnswer, thirdIncorrectAnswer) VALUES('" + it->question + "', '" + it->correctAnswer + "', '" + it->inncorrectAnswers[0] + "', '" + it->inncorrectAnswers[1] + "', '" + it->inncorrectAnswers[2] + "');");
		else if (it->inncorrectAnswers.size() == 2)
			sendQuery("INSERT INTO questions (question, correctAnswer, firstIncorrectAnswer, secondIncorrectAnswer, thirdIncorrectAnswer) VALUES('" + it->question + "', '" + it->correctAnswer + "', '" + it->inncorrectAnswers[0] + "', '" + it->inncorrectAnswers[1] + "', '');");
		else if (it->inncorrectAnswers.size() == 1)
			sendQuery("INSERT INTO questions (question, correctAnswer, firstIncorrectAnswer, secondIncorrectAnswer, thirdIncorrectAnswer) VALUES('" + it->question + "', '" + it->correctAnswer + "', '" + it->inncorrectAnswers[0] + "', '', '');");
	}
}

/*
this function will create a json data file using the website 'opentdb.com'
input: none
output: none
*/
void SqliteDatabase::createJsonFile() const
{
	if (S_OK != URLDownloadToFile(NULL, L"https://opentdb.com/api.php?amount=10", L"questions.txt", 0, NULL))
		throw dataBaseException("couldnt receive data from open api website.");
}

/*
this function will receive a callback function and a map and send the requested query
input: query, callback, counter
output: none
*/
void SqliteDatabase::sendQuery(const std::string query, int(callBack)(void* data, int argc, char** argv, char** azColName), std::map<string, std::pair<int, float>>* map)
{
	char* error = nullptr;
	int res = sqlite3_exec(_db, query.c_str(), callBack, map, &error);
	if (res != SQLITE_OK)
		throw dataBaseException(error);
}

/*
this function will send query with no pointer to a container
input: query, callback, print
output: bool - sended successfully or not
*/
void SqliteDatabase::sendQuery(const std::string query)
{
	char* error = nullptr;
	int res = sqlite3_exec(_db, query.c_str(), nullptr, nullptr, &error);
	if (res != SQLITE_OK)
		throw dataBaseException(error);
}

/*
this function will receive a callback function and a counter and send the requested query
input: query, callback, counter
output: none
*/
void SqliteDatabase::sendQuery(const std::string query, int(callBack)(void* data, int argc, char** argv, char** azColName), float* counter)
{
	char* error = nullptr;
	int res = sqlite3_exec(_db, query.c_str(), callBack, counter, &error);
	if (res != SQLITE_OK)
		throw dataBaseException(error);
}

/*
this function will be called if you need to count the appearence of a value in the data base and it will return the amount
of times this variable appears
input: data, argc, argv, azColName
output: int
*/
int callbackCounter(void* data, int argc, char** argv, char** azColName)
{
	float* counter = static_cast<float*>(data);
	*counter = atof(argv[0]);
	return 0;
}

/*
this function will receive a list of questions and insert to it the questions meta data
input: data, argc, argv, azColName
output: int
*/
int callBackQuestion(void* data, int argc, char** argv, char** azColName)
{
	std::list<questionMetaData>* questions = static_cast<std::list<questionMetaData>*>(data);
	questionMetaData question;
	for (int i = 0; i < argc; i++)
	{
		if (string(azColName[i]) == QUESTION)
			question.question = argv[i];
		else if (string(azColName[i]) == CORRECT_ANSWER)
			question.correctAnswer = argv[i];
		else if (string(azColName[i]) == FIRST_INCORRECT_ANSWER || string(azColName[i]) == SECOND_INCORRECT_ANSWER || string(azColName[i]) == THIRD_INCORRECT_ANSWER)
			question.inncorrectAnswers.push_back(argv[i]);
	}
	questions->push_back(question);
	return 0;
}

/*
this function will receive a list of map of the usernames and a pair of correct answers and the avarage time
input: data, argc, argv, azColName
output: int
*/
int callbackStats(void* data, int argc, char** argv, char** azColName)
{
	std::map<string, std::pair<int, float>>* users = static_cast<std::map<string, std::pair<int, float>>*>(data);
	std::pair<int, float> results;
	string username;
	for (int i = 0; i < argc; i++)
	{
		if (string(azColName[i]) == STATS_USER_NAME)
		{
			username = argv[i];
			(*users)[username];
		}
		else if (string(azColName[i]) == STATS_CORRECT_ANSWER)
			results.first = atoi(argv[i]);
		else if (string(azColName[i]) == STATS_AVG_ANSWER_TIME)
			results.second = atof(argv[i]);
	}
	(*users)[username] = results;
	return 0;
}
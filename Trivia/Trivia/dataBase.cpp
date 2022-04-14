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
	if (file_exist != 0)
	{
		try {
			sendQuery("create table if not exists clients(user_name TEXT PRIMARY KEY NOT NULL, password TEXT NOT NULL, email TEXT NOT NULL);");
			sendQuery("drop table if exists questions; create table if not exists questions(id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, question TEXT PRIMARY KEY NOT NULL, correctAnswer TEXT NOT NULL, firstIncorrectAnswer TEXT NOT NULL, secondIncorrectAnswer TEXT NOT NULL, thirdIncorrectAnswer TEXT NOT NULL);");
			initQuestionsTable();
		}
		catch (dataBaseException& e)
		{
			std::cerr << e.what() << std::endl;
			exit(1);
		}
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
	int count;
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
	int count;
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
	if (doesUserExist(username)) 
		std::cout << "username " + username + " already exists" << std::endl; 
	else
		sendQuery("insert into clients(user_name, password, email) values ('" + username + "', '" + password + "', '" + email + "');");
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
	std::ifstream file(URL);
	std::string line = "";
	std::string data = "";
	do {
		std::getline(file, line);
		data += line;
	} while (file.peek() != EOF);
	file.close();
	json jsonFromData = json::parse(data);
	results qs = jsonFromData;
	for (auto it : qs.resultsFromJson)
	{
		sendQuery("INSERT INTO questions (question, correctAnswer, firstIncorrectAnswer, secondIncorrectAnswer, thirdIncorrectAnswer) VALUES('" + it.question + "', '" + it.correctAnswer + "', '" + it.inncorrectAnswers[0] + "', '" + it.inncorrectAnswers[1] + "', '" + it.inncorrectAnswers[2] + "');");
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
void SqliteDatabase::sendQuery(const std::string query, int(callBack)(void* data, int argc, char** argv, char** azColName) , int* counter)
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
	int* counter = static_cast<int*>(data);
	*counter = atoi(argv[0]);
	return 0;
}

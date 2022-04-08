#pragma comment (lib, "ws2_32.lib")
#include "Infrastructure.h"
#include "WSAIntializer.h"

int main()
{
	try
	{
		SqliteDatabase* db = new SqliteDatabase();
		WSAInitializer wsaInit;
		server s(db);
		s.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error occured: " << e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "Unknown exception in main !" << std::endl;
	}
	return 0;
}
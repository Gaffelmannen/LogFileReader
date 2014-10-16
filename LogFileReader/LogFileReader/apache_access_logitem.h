#include <string>

using namespace std;

class apache_access_logitem
{
public:
	std::string ip;
	std::string date;
	std::string request;
	std::string url;
};
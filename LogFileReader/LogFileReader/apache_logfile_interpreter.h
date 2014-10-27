#include <string>
#include <iostream>
#include <vector>
#include "apache_access_logitem.h"

using namespace std;

class apache_logfile_interpreter
{
private:
	std::string find_in_row(string*, string);
	std::string find_in_row(string*, string, string);
	std::vector<std::string> split_in_row_in_two(string*, string);
public:
	apache_access_logitem interpret_row(string);
	int interpret_file(string);
};
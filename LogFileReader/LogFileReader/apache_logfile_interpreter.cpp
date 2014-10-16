#include "apache_logfile_interpreter.h"

apache_access_logitem apache_logfile_interpreter::interpret_row(string row)
{
	apache_access_logitem item;
	
	item.ip = apache_logfile_interpreter::find_in_row(&row, "- -");
	item.date = apache_logfile_interpreter::find_in_row(&row, "[", "]");
	item.request = apache_logfile_interpreter::find_in_row(&row, "\"", "\"");

	return item;
}

int apache_logfile_interpreter::interpret_file(string file_path)
{
	return 1;
}

string apache_logfile_interpreter::find_in_row(string* data, string delimter)
{
	std::string item = (*data);
	std::size_t pos = item.find(delimter);
	std::string str;

	if (pos != std::string::npos)
	{
		str = item.substr(0, pos - delimter.length());
		item = item.erase(0, pos);
	}

	return str;
}

string apache_logfile_interpreter::find_in_row(string* data, string delimter_one, string delimter_two)
{
	std::string item = (*data);

	std::size_t start_pos = item.find(delimter_one);
	std::size_t end_pos = item.substr(start_pos).find(delimter_two);
	std::string str;

	if (start_pos != std::string::npos && end_pos != std::string::npos)
	{
		str = item.substr(start_pos + delimter_one.length(), end_pos - delimter_two.length());
		item = item.erase(0, end_pos);
	}

	return str;
}
#include "apache_logfile_interpreter.h"

apache_access_logitem apache_logfile_interpreter::interpret_row(string row)
{
	apache_access_logitem item;
	
	item.ip = apache_logfile_interpreter::find_in_row(&row, "- -");
	item.date = apache_logfile_interpreter::find_in_row(&row, "[", "]");
	
	std::string tmp = apache_logfile_interpreter::find_in_row(&row, "\"", "\"");
	std::vector<std::string> parts = apache_logfile_interpreter::split_in_row_in_two(&tmp, "/");
	if(parts.size() > 1)
	{
		item.url = parts[0];
		item.request = parts[1];
	}

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
		str = item.substr(0, pos - 1);
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

std::vector<std::string> apache_logfile_interpreter::split_in_row_in_two(string* data, string delimter)
{
	std::string item = (*data);
	std::size_t pos = item.find(delimter);
	std::vector<std::string> parts;

	if (pos != std::string::npos)
	{
		parts.push_back(item.substr(0, pos - 1));
		parts.push_back(item.substr(pos, item.size() - pos - 1));
	}

	return parts;
}
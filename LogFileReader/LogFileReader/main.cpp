#include "main.h"
#include "filemanager.h"
#include "apache_logfile_interpreter.h"

char* filePath = "C:\\temp\\access_log";

int main() 
{
	cout << "Start" << endl;

	process_data();

	cout << "Doneskis" << endl;

	int i;
	cin >> i;
}

void process_data()
{
	FileManager fs;
	apache_logfile_interpreter ali;

	string data = fs.read_from_file(filePath);
	char delimeter = '\n';
	
	size_t pos;
	std::string row;
	size_t n = std::count(data.begin(), data.end(), delimeter);

	for(int i = 0; i < n; ++i)
	{
		pos = data.find(delimeter);
		row = data.substr(0, pos);

		apache_access_logitem item = ali.interpret_row(row);
		

		cout << item.ip << endl;

		data.erase(0, pos + sizeof(delimeter));
	}
}
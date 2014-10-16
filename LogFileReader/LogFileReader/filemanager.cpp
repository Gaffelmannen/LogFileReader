#include "filemanager.h"

int FileManager::get_size(string file_path)
{
	streampos begin,end;

	ifstream myfile (file_path, ios::binary);
	begin = myfile.tellg();
	myfile.seekg (0, ios::end);
	end = myfile.tellg();
	myfile.close();

	return (int)(end-begin);
}

string FileManager::read_from_file(string file_path)
{
	string content;

	ifstream the_file;
	the_file.open(file_path);

	if(the_file.is_open())
	{
		content = std::string((std::istreambuf_iterator<char>(the_file)), std::istreambuf_iterator<char>());
	}
	else
	{
		cout << "Unable to open file: " << file_path << endl;
	} 

	the_file.close();

	return content;
}

int FileManager::write_to_file(string content, string file_path)
{
	try
	{
		ofstream out(file_path, ios::out | ios::binary);

		if(!out) 
		{
			cout << "Cannot open output file." << endl;
			return 1;
		}

		char buffer[1024];
		strncpy(buffer, content.c_str(), sizeof(buffer));
		buffer[sizeof(buffer) - 1] = 0;

		out.write(buffer, strlen(buffer));

		out.close();
	
		return 0;
	}
	catch(std::exception e)
	{
		return 1;
	}
}
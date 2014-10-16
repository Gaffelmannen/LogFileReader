#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class FileManager
{
	int size;
public:
	int get_size(string filepath);
	string read_from_file(string);
	int write_to_file(string, string);
};
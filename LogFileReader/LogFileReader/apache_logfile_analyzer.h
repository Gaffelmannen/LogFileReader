#include <string>
#include <iostream>
#include <map>
#include <list>
#include <algorithm>

#include "apache_logfile_interpreter.h"
#include "apache_access_relative_occurence.h"
//#include "apache_access_logitem.h"

using namespace std;

typedef std::list<apache_access_logitem> log_list;
typedef std::map<string, log_list> log_map;
typedef std::pair<string, log_list> log_item;
typedef std::map<string, log_list>::iterator log_map_iterator;
typedef std::list<log_list>::const_iterator log_list_iterator;

class apache_logfile_analyzer
{
private:
	log_map items;

	std::vector<std::string> apache_logfile_analyzer::get_map_keys();
public:
	apache_logfile_analyzer();
	~apache_logfile_analyzer();

	int get_number_of_items();
	int add_to_items(apache_access_logitem);
	int remove_from_items(string);
	log_list find_in_items(string);
	std::vector<apache_access_relative_occurence> apache_logfile_analyzer::calculate_relative_occurence_of_each_ip();
};
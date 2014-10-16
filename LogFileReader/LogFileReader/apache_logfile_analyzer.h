#include <string>
#include <iostream>
#include <map>
#include "apache_access_logitem.h"

using namespace std;

typedef std::map<string, apache_access_logitem*> log_map;
typedef std::pair<string, apache_access_logitem*>* log_item;
typedef std::map<string, apache_access_logitem*>::iterator log_map_iterator;

class apache_logitem_analyzer
{
private:
	log_map items;
public:
	apache_logitem_analyzer();
	~apache_logitem_analyzer();

	int add_to_items(apache_access_logitem);
	int remove_from_items(string);
	apache_access_logitem* find_in_items(string);
};
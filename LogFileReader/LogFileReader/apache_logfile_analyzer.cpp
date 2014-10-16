#include "apache_logfile_analyzer.h"

apache_logitem_analyzer::apache_logitem_analyzer()
{

}

apache_logitem_analyzer::~apache_logitem_analyzer()
{

}

int apache_logitem_analyzer::add_to_items(apache_access_logitem access_log_item)
{
	if(find_in_items(access_log_item.ip) == NULL)
	{
		items[access_log_item.ip] = &access_log_item;

		return 0;
	}

	return 1;
}

int apache_logitem_analyzer::remove_from_items(string ip)
{
	items[ip] = NULL;
	return 0;
}

apache_access_logitem* apache_logitem_analyzer::find_in_items(string ipaddress)
{
	apache_access_logitem* item = NULL;

	log_map_iterator it = items.find(ipaddress);
	if(it != items.end())
	{
		item = it->second;
	}

	return item;
}
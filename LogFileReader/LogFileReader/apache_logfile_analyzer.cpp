#include "apache_logfile_analyzer.h"

apache_logfile_analyzer::apache_logfile_analyzer()
{

}

apache_logfile_analyzer::~apache_logfile_analyzer()
{

}

int apache_logfile_analyzer::get_number_of_items()
{
	return items.size();
}

int apache_logfile_analyzer::add_to_items(apache_access_logitem access_log_item)
{
	log_item item;
	item.first = access_log_item.ip;
	
	if(items.find(item.first)!=items.end())
	{
		items[item.first].push_back(access_log_item);
	}
	else
	{
		item.second.push_back(access_log_item);
		items.insert(item);
	}

	return 1;
}

int apache_logfile_analyzer::remove_from_items(string ip_address)
{
	items.erase(ip_address);

	return 0;
}

log_list apache_logfile_analyzer::find_in_items(string ip_address)
{
	log_list found_items;

	if(items.find(ip_address)!=items.end())
	{
		found_items = items[ip_address];
	}

	return found_items;
}

std::vector<apache_access_relative_occurence> apache_logfile_analyzer::calculate_relative_occurence_of_each_ip()
{
	std::vector<apache_access_relative_occurence> list;
	
	int total_number_of_logged_items = get_number_of_items();
	std::vector<std::string> keys = get_map_keys();

	for(int i = 0; i < keys.size(); ++i)
	{
		std::string key = keys[i];

		log_list logged_items_for_ip = find_in_items(key);

		apache_access_relative_occurence item;
		item.ip = key;
		item.number_of_occurences = logged_items_for_ip.size();
		item.percent = ((double)item.number_of_occurences) / ((double)total_number_of_logged_items) * 10;
		list.push_back(item);
	}

	std::sort(list.rbegin(), list.rend());

	return list;
}

std::vector<std::string> apache_logfile_analyzer::get_map_keys()
{
	std::vector<std::string> key_list;

	for(log_map_iterator it = items.begin(); it != items.end(); ++it) 
	{
		key_list.push_back(it->first);
	}

	return key_list;
}





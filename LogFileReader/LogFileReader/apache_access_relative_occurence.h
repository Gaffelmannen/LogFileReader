#include <string>

using namespace std;

class apache_access_relative_occurence
{
public:
	std::string ip;
	int number_of_occurences;
	double percent;

	bool operator> (apache_access_relative_occurence rhs) { return number_of_occurences>rhs.number_of_occurences; }
	bool operator< (apache_access_relative_occurence rhs) { return number_of_occurences<rhs.number_of_occurences; }
	bool apache_access_relative_occurence::sortDescending(const apache_access_relative_occurence &a,  const apache_access_relative_occurence &b) { return a.number_of_occurences<b.number_of_occurences; }
};


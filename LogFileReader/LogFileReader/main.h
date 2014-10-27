#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "apache_logfile_analyzer.h"
#include "network_client.h"
#include "network_server.h"

#define FILE_SIZE 10000;
#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

apache_logfile_analyzer ala;

void load_data(bool verbose);
void analyze_data(bool verbose);
void process_data(bool verbose);
void calculate_relative_occurence(bool verbose);

int init_network();

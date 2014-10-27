#include "main.h"
#include "filemanager.h"

char* filePath = "C:\\temp\\access_log";

int main() 
{
	bool verbose = 0;

	cout << "Start!" << endl;

	if(verbose)
	{
		cout << "Preparing to load data." << endl;
		load_data(verbose);
		cout << "Data loaded." << endl;

		cout << "Begin data analysis." << endl;
		analyze_data(verbose);
		cout << "Data analysis complete." << endl;
	}
	else
	{
		network_server net;
		net.setup();
		net.accept_connection();
		//net.foo();

		/*
		network_client net;
		net.setup("74.125.232.224", "80");
		net.send_message("GET / HTTP/1.1\r\n\r\n");
		*/
	}
	
	cout << "Doneskis!" << endl;
	cout << "Press Enter to exit" << endl;

	int i;
	cin >> i;

	exit(0);
}

void load_data(bool verbose)
{
	FileManager fs;
	apache_logfile_interpreter ali;

	string file_content = fs.read_from_file(filePath);
	char delimeter = '\n';

	size_t pos;
	std::string row;
	size_t number_of_rows = std::count(file_content.begin(), file_content.end(), delimeter);

	for(int i = 0; i < number_of_rows; ++i)
	{
		pos = file_content.find(delimeter);
		row = file_content.substr(0,  pos);

		apache_access_logitem item = ali.interpret_row(row);
		ala.add_to_items(item);
		
		if(verbose)
			cout << i << "(" << item.ip << ")" << "::" << ala.get_number_of_items() << endl;

		file_content.erase(0, pos + sizeof(delimeter));
	}
}

void analyze_data(bool verbose)
{
	calculate_relative_occurence(verbose);
	/*
	std::string ip_address_to_find = "64.242.88.10";

	log_list found_items = ala.find_in_items(ip_address_to_find);

	if(verbose)
		cout << " ====== " << found_items.size() << " ====== " << endl;
	*/
}

void process_data(bool verbose)
{
	FileManager fs;
	apache_logfile_interpreter ali;

	string data = fs.read_from_file(filePath);
	char delimeter = '\n';
	
	size_t pos;
	std::string row;
	size_t n = std::count(data.begin(), data.end(), delimeter);

	for( int i = 0; i < n; ++i )
	{
		pos = data.find(delimeter);
		row = data.substr(0, pos);

		apache_access_logitem item = ali.interpret_row(row);
		
		if(verbose)
			cout << item.ip << endl;

		data.erase(0, pos + sizeof(delimeter));
	}
}

void calculate_relative_occurence(bool verbose)
{
	printf("================================================================================\n");
	printf("Requests:\tPercent:\tNode:\n");
	printf("================================================================================\n");
	std::vector<apache_access_relative_occurence> items = ala.calculate_relative_occurence_of_each_ip();
	for(int i = 0; i < items.size(); ++i)
	{
		apache_access_relative_occurence item = items[i];
		if(item.percent >= 1.0)
		{
			cout << item.number_of_occurences << "\t\t" << item.percent << "\t\t" << item.ip << endl;
		}
		else
		{
			cout << item.number_of_occurences << "\t\t" << item.percent << "\t" << item.ip << endl;
		}
		//printf("%i\t\t%0.4d\t\t\t%s\n", item.number_of_occurences, item.percent, item.ip.c_str());
	}
	printf("================================================================================\n");
}

int init_network()
{
	WSADATA wsa;
    SOCKET s;
    struct sockaddr_in server;
    char *message , server_reply[2000];
    int recv_size;
 
    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        return 1;
    }
     
    printf("Initialised.\n");
     
    //Create a socket
    if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d" , WSAGetLastError());
    }
 
    printf("Socket created.\n");
     
     
    server.sin_addr.s_addr = inet_addr("74.125.232.224");
    server.sin_family = AF_INET;
    server.sin_port = htons( 80 );
 
    //Connect to remote server
    if (connect(s , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("connect error");
        return 1;
    }
     
    puts("Connected");
     
    //Send some data
    message = "GET / HTTP/1.1\r\n\r\n";
    if( send(s , message , strlen(message) , 0) < 0)
    {
        puts("Send failed");
        return 1;
    }
    puts("Data Send\n");
     
    //Receive a reply from the server
    if((recv_size = recv(s , server_reply , 2000 , 0)) == SOCKET_ERROR)
    {
        puts("recv failed");
    }
     
    puts("Reply received\n");
 
    //Add a NULL terminating character to make it a proper string before printing
    server_reply[recv_size] = '\0';
    puts(server_reply);
}
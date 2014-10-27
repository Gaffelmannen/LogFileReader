#include "network_client.h"

network_client::network_client()
{
	
}

network_client::~network_client()
{
	disconnect();
}

int network_client::init()
{
	printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        return 1;
    }
     
    printf("Initialised.\n");

	return 0;
}

int network_client::create_socket(std::string ip_address, std::string port)
{
	//Create a socket
    if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d" , WSAGetLastError());
    }
 
    printf("Socket created.\n");

	return 0;
}

int network_client::connect_socket()
{
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

	return 0;
}

int network_client::setup(std::string ip_address, std::string port)
{
	init();

	create_socket(ip_address, port);

	connect_socket();

	return 0;
}

int network_client::disconnect()
{
	closesocket(s);
	WSACleanup();

	return 0;
}

int network_client::send_message(std::string message)
{
	//Send some data
    message = "GET / HTTP/1.1\r\n\r\n";
    if( send(s , message.c_str() , strlen(message.c_str()) , 0) < 0)
    {
        puts("Send failed");
        return 1;
    }
    puts("Data Send\n");
     
    if((recv_size = recv(s , server_reply , 2000 , 0)) == SOCKET_ERROR)
    {
        puts("recv failed");
    }
     
    puts("Reply received\n");
 
    server_reply[recv_size] = '\0';
    puts(server_reply);

	return 0;
}

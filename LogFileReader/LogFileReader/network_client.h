#include <winsock2.h>
#include <string>
#include <Ws2tcpip.h>
#include <windows.h>

using namespace std;

#pragma comment(lib, "ws2_32.lib")

#define RECEIVE_BUFFER_SIZE 1024
#define errno WSAGetLastError()

class network_client
{
private:
	WSADATA wsa;
    SOCKET s;
    struct sockaddr_in server;
    char *message , server_reply[2000];
    int recv_size;

	int network_client::init();
	int network_client::create_socket(std::string ip_address, std::string port);
	int network_client::connect_socket();

public:
	network_client::network_client();
	network_client::~network_client();

	int network_client::setup(std::string ip_address, std::string port);
	int network_client::disconnect();

	int network_client::send_message(std::string message);

};
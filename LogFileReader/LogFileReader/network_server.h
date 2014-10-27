#undef UNICODE

#include <winsock2.h>
#include <string>
#include <Ws2tcpip.h>
#include <windows.h>

#pragma comment (lib, "Ws2_32.lib")
//#pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"


class network_server
{
private:
	WSADATA wsaData;
    int iResult;

    SOCKET ListenSocket;
    SOCKET ClientSocket;

    struct addrinfo *result;
    struct addrinfo hints;

    int iSendResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen;

	int network_server::init();
	int network_server::create_socket();
	int network_server::connect_socket();
    
public:

	network_server::network_server();
	network_server::~network_server();

	int network_server::setup();
	int network_server::listen_socket();
	int network_server::accept_connection();

	int network_server::foo();
};
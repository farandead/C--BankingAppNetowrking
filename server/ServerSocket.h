#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")


class ServerSocket{
public:
    ServerSocket(int port);
    ~ServerSocket();
    bool start();
    SOCKET acceptClient();

    std::string receive(SOCKET clientSocket);
    bool  send(SOCKET clientSocket, const std::string &message);
    void closeServer();

private:
    SOCKET serverSocket ;
    int port;
    struct sockaddr_in serverAddr;
    static const int BACKLOG = 5;
};


#endif // SERVERSOCKET_H
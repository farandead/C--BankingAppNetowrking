#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <string>
#include <winsock2.h>
#pragma comment(lib, "Ws2_32.lib")



class ClientSocket
{
    public:
        ClientSocket();
        ~ClientSocket();
        bool connectToServer(const std::string &serverIP, int port);
        bool sendMessage(const std::string &message);
        std::string receiveMessage();
        void disconnect();
    private:
        int sockfd;
        struct sockaddr_in serverAddr;
        bool initializeSocket();
        void cleanupSocket();
        bool sendLoginRequest(const std::string &username, const std::string &password);
};

#endif // CLIENTSOCKET_H
        

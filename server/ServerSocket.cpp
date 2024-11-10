#include<iostream>
#include "ServerSocket.h"
#include <string>
using namespace std;

ServerSocket::ServerSocket(int port): port(port)
{
    serverSocket = INVALID_SOCKET;
    memset(&serverAddr, 0, sizeof(serverAddr));
}


ServerSocket::~ServerSocket()
{
    closeServer();
}

bool ServerSocket::start(){

    WSADATA wsaData;
    int iResult;
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        std::cerr << "WSAStartup failed: " << iResult << std::endl;
        WSACleanup();
        return false;
    }

    serverSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET){
        cerr<<"Error creating socket"<<WSAGetLastError()<<endl;
        WSACleanup();
        return false;

    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    if(bind(serverSocket, (struct sockaddr*) &serverAddr, sizeof(serverAddr)) == SOCKET_ERROR){
        cerr<<"Bind failed with error: "<<WSAGetLastError()<<endl;
        closesocket(serverSocket);
        WSACleanup();
        return false;

    }
    if (listen(serverSocket,BACKLOG) == SOCKET_ERROR){
        cerr<<"Listen failed with error: "<<WSAGetLastError()<<endl;
        closesocket(serverSocket);
        WSACleanup();
        return false;
    }
    cout<<"Server started on port: "<<port<<endl;
    return true;

};

SOCKET ServerSocket::acceptClient(){
    struct  sockaddr_in clientAddr;
    int clientAddrSize = sizeof(clientAddr);
    SOCKET clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrSize);
    if (clientSocket == INVALID_SOCKET){
        cerr<<"Accept failed with an error: "<<WSAGetLastError()<<endl;
        return INVALID_SOCKET;
    };
    return clientSocket;
    
};

string ServerSocket::receive(SOCKET clientSocket){
    char buffer[1024];
    memset(buffer,0,sizeof(buffer));
    int bytesRecv = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesRecv == SOCKET_ERROR){
        cerr<<"Receive failed with error: "<<WSAGetLastError()<<endl;
        return "";
    }
    else if (bytesRecv == 0){
        cerr<<"Connection closed"<<endl;
        return "";
    }
    return string(buffer);
};


bool  ServerSocket::send(SOCKET clientSocket, const string &messages){
    int bytesSent = ::send(clientSocket, messages.c_str(), messages.size(), 0);
    if (bytesSent == SOCKET_ERROR){
        cerr<<"Send failed with error: "<<WSAGetLastError()<<endl;
        return false;
    }

    return true;

}

void ServerSocket::closeServer(){
   if (serverSocket != INVALID_SOCKET){
       closesocket(serverSocket);
       WSACleanup();
       cout<<"Server closed"<<endl;
   }
}

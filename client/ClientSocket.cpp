#include "ClientSocket.h"
#include <iostream>
#include <sstream>
#include "Protocol.h"

#ifdef _WIN32
#include <ws2tcpip.h> // For Windows IP functions
#else
#include <arpa/inet.h> // For Unix IP functions
#include <cstring>      // For memset on Unix
#endif

ClientSocket::ClientSocket() : sockfd(-1) {
    if (!initializeSocket()) {
        std::cerr << "Error initializing socket." << std::endl;
    }
}

bool ClientSocket::sendLoginRequest(const std::string& username, const std::string& password) {
    std::ostringstream oss;
    oss << "LOGIN " << username << " " << password;
    std::string loginRequest = oss.str();

    if (!sendMessage(loginRequest)) {
        std::cerr << "Failed to send login request." << std::endl;
        return false;
    }

    std::string response = receiveMessage();
    if (response.empty()) {
        std::cerr << "No response received from server." << std::endl;
        return false;
    }

    std::istringstream iss(response);
    int responseTypeInt;
    std::string message;

    iss >> responseTypeInt >> message;
    return (responseTypeInt == static_cast<int>(ResponseType::SUCCESS));
}

ClientSocket::~ClientSocket() {
    disconnect();
    cleanupSocket();
}

bool ClientSocket::initializeSocket() {
#ifdef _WIN32
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        std::cerr << "WSAStartup failed: " << iResult << std::endl;
        return false;
    }
#endif
    return true;
}

void ClientSocket::cleanupSocket() {
#ifdef _WIN32
    WSACleanup();
#endif
}

bool ClientSocket::connectToServer(const std::string& serverIP, int port) {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "Error creating socket." << std::endl;
        return false;
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);

#ifdef _WIN32
    // Use inet_addr for Windows
    serverAddr.sin_addr.s_addr = inet_addr(serverIP.c_str());
    if (serverAddr.sin_addr.s_addr == INADDR_NONE) {
        std::cerr << "Invalid address or address not supported." << std::endl;
        return false;
    }
#else
    // Use inet_pton for Unix-based systems
    if (inet_pton(AF_INET, serverIP.c_str(), &serverAddr.sin_addr) <= 0) {
        std::cerr << "Invalid address or address not supported." << std::endl;
        return false;
    }
#endif

    if (connect(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Connection failed." << std::endl;
        return false;
    }

    return true;
}

bool ClientSocket::sendMessage(const std::string& message) {
    if (send(sockfd, message.c_str(), message.length(), 0) <= 0) {
        std::cerr << "Error sending message." << std::endl;
        return false;
    }
    return true;
}

std::string ClientSocket::receiveMessage() {
    char buffer[1024] = {0};
    int valread = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
    if (valread <= 0) {
        std::cerr << "Error or connection closed by server." << std::endl;
        return "";
    }
    buffer[valread] = '\0';

    return std::string(buffer);
}

void ClientSocket::disconnect() {
    if (sockfd >= 0) {
#ifdef _WIN32
        closesocket(sockfd);
#else
        close(sockfd);
#endif
        sockfd = -1;
    }
}
#include "ServerSocket.h"
#include "BankOperations.h"
#include "Protocol.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <experimental/optional>

void handleClient(ServerSocket &server, SOCKET clientSocket, BankOperations &bankOperations)
{
    while (true)
    {
        // Receive request from client
        std::string receivedData = server.receive(clientSocket);
        if (receivedData.empty())
        {
            std::cout << "Client disconnected." << std::endl;
            break;
        }

        // Deserialize received data to a Request object
        Request request;
        std::istringstream iss(receivedData);

        int requestTypeInt;
        iss >> requestTypeInt; // Read as integer
        request.type = static_cast<RequestType>(requestTypeInt);

        // Parse additional request data based on the request type
        if (request.type == RequestType::LOGIN)
        {
            std::string password;
            iss >> password;
            request.password = password; // Set optional password
        }
        else if (request.type == RequestType::DEPOSIT || request.type == RequestType::WITHDRAW)
        {
            double amount;
            iss >> amount;
            request.amount = amount; // Set optional amount
        }
        else if (request.type == RequestType::TRANSFER)
        {
            std::string targetUser;
            double amount;
            iss >> targetUser >> amount;
            request.targetUser = targetUser;
            request.amount = amount;
        }

        // Create a Response object
        Response response;

        // Handle the request based on the request type
        switch (request.type)
        {
        case RequestType::LOGIN:
        {
            UserRole role;
            bool success = bankOperations.authenticateUser(request.username, *request.password, role); // Use * to access optional value
            response.type = success ? ResponseType::SUCCESS : ResponseType::FAILURE;
            response.message = success ? "Login successful" : "Login failed";
            break;
        }
        case RequestType::DEPOSIT:
        {
            bool success = bankOperations.deposit(request.username, *request.amount); // Use * to access optional value
            response.type = success ? ResponseType::SUCCESS : ResponseType::FAILURE;
            response.message = success ? "Deposit successful" : "Deposit failed";
            break;
        }
        case RequestType::WITHDRAW:
        {
            bool success = bankOperations.withdraw(request.username, *request.amount); // Use * to access optional value
            response.type = success ? ResponseType::SUCCESS : ResponseType::FAILURE;
            response.message = success ? "Withdrawal successful" : "Insufficient funds";
            break;
        }
        case RequestType::CHECK_BALANCE:
        {
            double balance = bankOperations.checkBalance(request.username);
            response.type = (balance != -1) ? ResponseType::SUCCESS : ResponseType::FAILURE;
            response.message = (balance != -1) ? "Balance retrieved" : "Account not found";
            response.balance = balance;
            break;
        }
        case RequestType::VIEW_ALL_ACCOUNTS:
        {
            std::vector<std::string> accounts = bankOperations.viewAllAccounts(request.role.value()); // Use value() to access optional value
            response.type = ResponseType::SUCCESS;
            response.accounts = accounts;
            response.message = "All accounts retrieved";
            break;
        }
        // Add other cases for different request types like TRANSFER, CREATE_ACCOUNT, DELETE_ACCOUNT
        default:
            response.type = ResponseType::FAILURE;
            response.message = "Unknown request type";
            break;
        }

        // Serialize and send the response back to the client
        std::ostringstream oss;
        oss << static_cast<int>(response.type) << " " << response.message;
        if (response.balance) {   // Check if balance has a value
            oss << " " << *response.balance; // Use * to dereference and access the value
        }
        if (!server.send(clientSocket, oss.str())) {
            std::cerr << "Error sending response to client." << std::endl;
        }
    }

    // Close the client socket after handling the request
    closesocket(clientSocket);
}


int main(){
    int port = 8080;
    ServerSocket server(port);
    if (!server.start())
    {
        std::cerr << "Error starting server." << std::endl;
        return 1;
    }

    FileHandler fileHandler;
    BankOperations bankOperations(fileHandler); 

    while (true)
    {
        SOCKET clientSocket = server.acceptClient();
        if (clientSocket != INVALID_SOCKET)
        {
            std::cout << "Client connected." << std::endl;
            handleClient(server, clientSocket, bankOperations);

            closesocket(clientSocket);
        }
    
    }

    server.closeServer();
    return 0;
};
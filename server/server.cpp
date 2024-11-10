#include "ServerSocket.h"
#include "BankOperations.h"
#include "Protocol.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <experimental/optional>



void handleClient(ServerSocket &server, SOCKET clientSocket, BankOperations &bankOperations) {
    while (true) {
     
        std::string receivedData = server.receive(clientSocket);
        if (receivedData.empty()) {
            std::cout << "Client disconnected." << std::endl;
            break;
        }

        // Deserialize received data to a Request object
        Request request;
        std::istringstream iss(receivedData);

        std::string requestTypeStr;
        iss >> requestTypeStr;

        // Map the request type string to the RequestType enum
        if (requestTypeStr == "DEPOSIT") {
            request.type = RequestType::DEPOSIT;
        } else if (requestTypeStr == "WITHDRAW") {
            request.type = RequestType::WITHDRAW;
        } else if (requestTypeStr == "TRANSFER") {
            request.type = RequestType::TRANSFER;
        } else if (requestTypeStr == "CHECK_BALANCE") {
            request.type = RequestType::CHECK_BALANCE;
        } else if (requestTypeStr == "VIEW_ACCOUNT") {
            request.type = RequestType::VIEW_ACCOUNT;
        } else if (requestTypeStr == "VIEW_ALL_ACCOUNTS") {
            request.type = RequestType::VIEW_ALL_ACCOUNTS;
        } else if (requestTypeStr == "CREATE_ACCOUNT") {
            request.type = RequestType::CREATE_ACCOUNT;
        } else if (requestTypeStr == "DELETE_ACCOUNT") {
            request.type = RequestType::DELETE_ACCOUNT;
        } else {
            std::cerr << "Invalid request type: " << requestTypeStr << std::endl;
            return; 
        }

     
        if (request.type == RequestType::DEPOSIT || request.type == RequestType::WITHDRAW) {
            std::string username;
            double amount;
            iss >> username >> amount;
            request.username = username;
            request.amount = amount;
        } else if (request.type == RequestType::TRANSFER) {
            std::string username, targetUser;
            double amount;
            iss >> username >> targetUser >> amount;
            request.username = username;
            request.targetUser = targetUser;
            request.amount = amount;
        } else if (request.type == RequestType::CHECK_BALANCE) {
            std::string username;
            iss >> username;
            request.username = username;
        } else if (request.type == RequestType::VIEW_ACCOUNT) {
            std::string username;
            iss >> username;
            request.username = username;
        } else if (request.type == RequestType::VIEW_ALL_ACCOUNTS) {
            // Directly grant access to view all accounts without role checks
            request.type = RequestType::VIEW_ALL_ACCOUNTS;
        } else if (request.type == RequestType::CREATE_ACCOUNT) {
            std::string username, password;
            iss >> username >> password;
            request.username = username;
            request.password = password;
        } else if (request.type == RequestType::DELETE_ACCOUNT) {
            std::string username;
            iss >> username;
            request.username = username;
        }

        Response response;

    
        switch (request.type) {
        case RequestType::DEPOSIT: {
            bool success = bankOperations.deposit(request.username, *request.amount);
            response.type = success ? ResponseType::SUCCESS : ResponseType::FAILURE;
            response.message = success ? "Deposit successful" : "Deposit failed";
            break;
        }
        case RequestType::WITHDRAW: {
            bool success = bankOperations.withdraw(request.username, *request.amount);
            response.type = success ? ResponseType::SUCCESS : ResponseType::FAILURE;
            response.message = success ? "Withdrawal successful" : "Insufficient funds";
            break;
        }
        case RequestType::CHECK_BALANCE: {
            double balance = bankOperations.checkBalance(request.username);
            response.type = (balance != -1) ? ResponseType::SUCCESS : ResponseType::FAILURE;
            response.message = (balance != -1) ? "Balance retrieved" : "Account not found";
            response.balance = balance;
            break;
        }
        case RequestType::VIEW_ALL_ACCOUNTS: {
            std::vector<std::string> accounts = bankOperations.viewAllAccounts(UserRole::MANAGER);
            response.type = ResponseType::SUCCESS;
            response.accounts = accounts;
            response.message = "All accounts retrieved";
            break;
        }
        case RequestType::VIEW_ACCOUNT: {
            std::string accountDetails = bankOperations.viewAccount(request.username, UserRole::MANAGER);
            response.type = ResponseType::SUCCESS;
            response.account = accountDetails;
            response.message = "Account details retrieved";
            break;
        }
        case RequestType::CREATE_ACCOUNT: {
            bool success = bankOperations.createAccount(request.username, *request.password, UserRole::USER);
            response.type = success ? ResponseType::SUCCESS : ResponseType::FAILURE;
            response.message = success ? "Account created" : "Account creation failed";
            break;
        }
        case RequestType::TRANSFER: {
            bool success = bankOperations.transfer(request.username, *request.targetUser, *request.amount);
            response.type = success ? ResponseType::SUCCESS : ResponseType::FAILURE;
            response.message = success ? "Transfer successful" : "Transfer failed";
            break;
          
        }
        default:
            response.type = ResponseType::FAILURE;
            response.message = "Unknown request type";
            break;
        }

        std::ostringstream oss;
        oss << static_cast<int>(response.type) << " " << response.message;
        if (response.balance) { 
            oss << " " << *response.balance; 
        }
        if (!server.send(clientSocket, oss.str())) {
            std::cerr << "Error sending response to client." << std::endl;
        }
    }

    closesocket(clientSocket);
}

int main() {
    int port = 8080;
    ServerSocket server(port);
    if (!server.start()) {
        std::cerr << "Error starting server." << std::endl;
        return 1;
    }

    FileHandler fileHandler;
    BankOperations bankOperations(fileHandler);

    while (true) {
        SOCKET clientSocket = server.acceptClient();
        if (clientSocket != INVALID_SOCKET) {
            std::cout << "Client connected." << std::endl;
            handleClient(server, clientSocket, bankOperations);

            closesocket(clientSocket);
        }
    }

    server.closeServer();
    return 0;
}


# Banking System with Networked Client-Server Architecture

This project is a simple banking system implemented using a networked client-server architecture. It allows clients to perform basic banking operations such as logging in, depositing and withdrawing money, checking balances, and transferring funds. The server is implemented using sockets to manage client connections and communication, with session-based authentication to maintain user state during interactions.

### Features

- **Client-Server Architecture**: Uses a TCP/IP socket connection to handle client requests and server responses.
- **Session-Based Authentication**: Users log in once and maintain their session without re-authenticating for each action.
- **Role-Based Access Control**: Differentiates between standard users and managers, allowing managers additional privileges such as viewing all accounts.
- **Banking Operations**: Provides functionality for deposit, withdrawal, balance checks, transfers, and more.
- **Enum-Based Request-Response Protocol**: Utilizes `RequestType` and `ResponseType` enums for structured and type-safe communication.
- **C++14 Compatibility**: Uses `std::experimental::optional` for optional fields.

### Project Structure

```plaintext
BankingSystem/
├── client/
│   ├── Client.cpp             // Main client code, handles UI and connects to server
│   ├── ClientSocket.cpp       // Manages client-side socket setup and communication
│   ├── ClientSocket.h         // Header for ClientSocket.cpp
│   ├── UserInterface.cpp      // Manages displaying options and gathering user input
│   └── UserInterface.h        // Header for UserInterface.cpp
├── server/
│   ├── Server.cpp             // Main server code, handles client connections and requests
│   ├── ServerSocket.cpp       // Manages server-side socket setup and listening
│   ├── ServerSocket.h         // Header for ServerSocket.cpp
│   ├── BankOperations.cpp     // Implements core banking functionalities
│   ├── BankOperations.h       // Header for BankOperations.cpp
│   ├── FileHandler.cpp        // Manages file-based storage for user data and transaction history
│   └── FileHandler.h          // Header for FileHandler.cpp
├── common/
│   ├── Protocol.h             // Defines the request and response protocol
│   └── Utils.h                // Helper functions for error handling and data conversion
└── README.md                  // Project overview and instructions
```

### Getting Started

1. **Dependencies**: Ensure you have a C++ compiler that supports C++14 or higher (e.g., g++ 5.4+, Visual Studio 2017+).
2. **Compilation**: Compile the project using the provided Makefile or any C++ build system.
3. **Run Server**: Start the server to listen for incoming client connections.
   ```bash
   ./server/Server
   ```
4. **Run Client**: Run the client to connect to the server and interact with the banking system.
   ```bash
   ./client/Client
   ```

### Example Workflow

1. **Start the Server**: The server listens on a specified port, awaiting client connections.
2. **Client Login**: A client connects and sends a login request. The server authenticates and creates a session.
3. **Banking Operations**: The client can perform various actions:
   - **Deposit/Withdraw**: Add or remove funds from their account.
   - **Transfer**: Move funds to another user’s account.
   - **Check Balance**: View their current account balance.
4. **End Session**: When finished, the client logs out, and the server closes the connection.

### Request and Response Protocol

The client-server communication is based on a protocol that uses `RequestType` and `ResponseType` enums for structured communication:

- **Requests**:
  - `LOGIN`, `DEPOSIT`, `WITHDRAW`, `TRANSFER`, `CHECK_BALANCE`, etc.
- **Responses**:
  - `SUCCESS` or `FAILURE` status, along with optional data fields like `balance` or `message`.

### Future Improvements

- Implement database storage for more robust data persistence.
- Add encryption for secure communication.
- Develop a graphical client interface for enhanced usability.

### License

This project is open-source and available under the MIT License.

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++14 -Wall -Icommon

# Directories
CLIENT_DIR = client
SERVER_DIR = server
COMMON_DIR = common

# Output executables
CLIENT_TARGET = BankingClient
SERVER_TARGET = BankingServer

# Object files
CLIENT_OBJS = $(CLIENT_DIR)/Client.o $(CLIENT_DIR)/ClientSocket.o $(CLIENT_DIR)/UserInterface.o
SERVER_OBJS = $(SERVER_DIR)/Server.o $(SERVER_DIR)/ServerSocket.o $(SERVER_DIR)/BankOperations.o $(SERVER_DIR)/FileHandler.o

TARGETS = $(CLIENT_TARGET) $(SERVER_TARGET)

all: $(TARGETS)

# Client executable with Winsock library
$(CLIENT_TARGET): $(CLIENT_OBJS)
	$(CXX) $(CXXFLAGS) -o $(CLIENT_TARGET) $(CLIENT_OBJS) -lws2_32

# Server executable with Winsock library
$(SERVER_TARGET): $(SERVER_OBJS)
	$(CXX) $(CXXFLAGS) -o $(SERVER_TARGET) $(SERVER_OBJS) -lws2_32

# Compile Client.cpp
$(CLIENT_DIR)/Client.o: $(CLIENT_DIR)/Client.cpp $(CLIENT_DIR)/ClientSocket.h $(CLIENT_DIR)/UserInterface.h $(COMMON_DIR)/Protocol.h
	$(CXX) $(CXXFLAGS) -c $(CLIENT_DIR)/Client.cpp -o $(CLIENT_DIR)/Client.o

# Compile ClientSocket.cpp
$(CLIENT_DIR)/ClientSocket.o: $(CLIENT_DIR)/ClientSocket.cpp $(CLIENT_DIR)/ClientSocket.h
	$(CXX) $(CXXFLAGS) -c $(CLIENT_DIR)/ClientSocket.cpp -o $(CLIENT_DIR)/ClientSocket.o

# Compile UserInterface.cpp
$(CLIENT_DIR)/UserInterface.o: $(CLIENT_DIR)/UserInterface.cpp $(CLIENT_DIR)/UserInterface.h
	$(CXX) $(CXXFLAGS) -c $(CLIENT_DIR)/UserInterface.cpp -o $(CLIENT_DIR)/UserInterface.o

# Compile Server.cpp
$(SERVER_DIR)/Server.o: $(SERVER_DIR)/Server.cpp $(SERVER_DIR)/ServerSocket.h $(SERVER_DIR)/BankOperations.h $(COMMON_DIR)/Protocol.h
	$(CXX) $(CXXFLAGS) -c $(SERVER_DIR)/Server.cpp -o $(SERVER_DIR)/Server.o

# Compile ServerSocket.cpp
$(SERVER_DIR)/ServerSocket.o: $(SERVER_DIR)/ServerSocket.cpp $(SERVER_DIR)/ServerSocket.h
	$(CXX) $(CXXFLAGS) -c $(SERVER_DIR)/ServerSocket.cpp -o $(SERVER_DIR)/ServerSocket.o

# Compile BankOperations.cpp
$(SERVER_DIR)/BankOperations.o: $(SERVER_DIR)/BankOperations.cpp $(SERVER_DIR)/BankOperations.h $(SERVER_DIR)/FileHandler.h
	$(CXX) $(CXXFLAGS) -c $(SERVER_DIR)/BankOperations.cpp -o $(SERVER_DIR)/BankOperations.o

# Compile FileHandler.cpp
$(SERVER_DIR)/FileHandler.o: $(SERVER_DIR)/FileHandler.cpp $(SERVER_DIR)/FileHandler.h
	$(CXX) $(CXXFLAGS) -c $(SERVER_DIR)/FileHandler.cpp -o $(SERVER_DIR)/FileHandler.o

.PHONY: clean
clean:
	rm -f $(CLIENT_OBJS) $(SERVER_OBJS) $(TARGETS)

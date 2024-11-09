# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Directories
SERVER_DIR = server

# Object files
OBJS = $(SERVER_DIR)/BankOperations.o $(SERVER_DIR)/FileHandler.o $(SERVER_DIR)/main.o

# Output executable
TARGET = TestBankOperations

# Target rule to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile main.cpp
$(SERVER_DIR)/main.o: $(SERVER_DIR)/main.cpp $(SERVER_DIR)/BankOperations.h $(SERVER_DIR)/FileHandler.h
	$(CXX) $(CXXFLAGS) -c $(SERVER_DIR)/main.cpp -o $(SERVER_DIR)/main.o

# Compile BankOperations.cpp
$(SERVER_DIR)/BankOperations.o: $(SERVER_DIR)/BankOperations.cpp $(SERVER_DIR)/BankOperations.h $(SERVER_DIR)/FileHandler.h
	$(CXX) $(CXXFLAGS) -c $(SERVER_DIR)/BankOperations.cpp -o $(SERVER_DIR)/BankOperations.o

# Compile FileHandler.cpp
$(SERVER_DIR)/FileHandler.o: $(SERVER_DIR)/FileHandler.cpp $(SERVER_DIR)/FileHandler.h
	$(CXX) $(CXXFLAGS) -c $(SERVER_DIR)/FileHandler.cpp -o $(SERVER_DIR)/FileHandler.o

# Clean rule
.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)
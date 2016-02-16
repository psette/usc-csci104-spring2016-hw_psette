CXX = g++
CPPFLAGS = -g -Wall
BIN_DIR = bin
GTEST_LL = -I /usr/local/opt/gtest/include/ -l gtest -l gtest_main -pthread

all:  stackint llisttest 
stackint: stackint.cpp llistint.cpp sape.cpp sape.cpp $(BIN_DIR)/.dirstamp
	$(CXX) $(CPPFLAGS) stackint.cpp llistint.cpp sape.cpp -o $(BIN_DIR)/stackint
	./$(BIN_DIR)/stackint in.txt
	
llisttest : llistint.cpp llistint.h test.cpp  $(BIN_DIR)/.dirstamp
	$(CXX) $(CPPFLAGS) llistint.cpp test.cpp $(GTEST_LL) -o $(BIN_DIR)/llisttest 
	./$(BIN_DIR)/llisttest 



.PHONY: clean

clean:
	rm -rf $(BIN_DIR)

$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp
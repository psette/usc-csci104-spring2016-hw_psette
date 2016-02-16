CXX = g++
CPPFLAGS = -g -Wall
BIN_DIR = bin
GTEST_LL = -I /usr/local/opt/gtest/include/ -l gtest -l gtest_main -pthread
LIST_DEPEN = stackint.cpp llistint.cpp
all:  sape llisttest stackint

sape : $(LIST_DEPEN) sape.cpp $(BIN_DIR)/.dirstamp
	$(CXX) $(CPPFLAGS) $(LIST_DEPEN) sape.cpp -o $(BIN_DIR)/sape

llisttest : llistint.cpp llistint.h listtest.cpp  $(BIN_DIR)/.dirstamp
	$(CXX) $(CPPFLAGS) llistint.cpp listtest.cpp $(GTEST_LL) -o $(BIN_DIR)/llisttest 


stackint : $(LIST_DEPEN) stacktest.cpp $(BIN_DIR)/.dirstamp
	$(CXX) $(CPPFLAGS) $(LIST_DEPEN) stacktest.cpp $(GTEST_LL) -o $(BIN_DIR)/stacktest

.PHONY: clean

clean:
	rm -rf $(BIN_DIR)

$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp
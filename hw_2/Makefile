CXX = g++
CPPFLAGS = -g -Wall
BIN_DIR = bin

all:  llistint
	./$(BIN_DIR)/llistint

llistint: llistint.cpp test.cpp test.cpp $(BIN_DIR)/.dirstamp
	$(CXX) $(CPPFLAGS) llistint.cpp test.cpp -o $(BIN_DIR)/llistint

.PHONY: clean

clean:
	rm -rf $(BIN_DIR)

$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp
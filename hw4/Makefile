CXX = g++
CPPFLAGS = -g -Wall
BIN_DIR =bin
TARGETS = $(BIN_DIR)/AddStatement.o $(BIN_DIR)/DivStatement.o $(BIN_DIR)/EndStatement.o $(BIN_DIR)/GotoStatement.o $(BIN_DIR)/GosubStatement.o $(BIN_DIR)/GotoStatement.o $(BIN_DIR)/IfStatement.o $(BIN_DIR)/LetStatement.o $(BIN_DIR)/llistint.o $(BIN_DIR)/MultStatement.o $(BIN_DIR)/PrintStatement.o $(BIN_DIR)/ProgramState.o $(BIN_DIR)/RetrStatement.o $(BIN_DIR)/stackint.o $(BIN_DIR)/SubtStatement.o $(BIN_DIR)/PrALLStatement.o

make: all

$(BIN_DIR)/%.o: src/%.cpp lib/%.h $(BIN_DIR)/.dirstamp 
	$(CC) $(CPPFLAGS) -c $< -o $@

all: Facile.cpp $(TARGETS)
	$(CXX) $(CPPFLAGS) $^  -o $(BIN_DIR)/Facile

clean:
	rm -rf $(BIN_DIR)

.PHONY: clean

$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp
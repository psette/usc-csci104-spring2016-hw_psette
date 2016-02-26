// Facile.cpp
#include "Statement.h"
#include "lib/PrALLStatement.h"
#include "lib/LetStatement.h"
#include "lib/AddStatement.h"
#include "lib/SubtStatement.h"
#include "lib/MultStatement.h"
#include "lib/DivStatement.h"
#include "lib/RetrStatement.h"
#include "lib/GotoStatement.h"
#include "lib/GosubStatement.h"
#include "lib/IfStatement.h"
#include "lib/EndStatement.h"
#include "lib/PrintStatement.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream> 
#include <fstream>
#include <cstdlib>
using namespace std;
// parseProgram() takes a filename as a parameter, opens and reads the
// contents of the file, and returns an vector of pointers to Statement.
void parseProgram(istream& inf, vector<Statement *> & program);
// parseLine() takes a line from the input file and returns a Statement
// pointer of the appropriate type.  This will be a handy method to call
// within your parseProgram() method.
Statement * parseLine(string line);
// interpretProgram() reads a program from the given input stream
// and interprets it, writing any output to the given output stream.
// Note:  you are required to implement this function!
void interpretProgram(istream& inf, ostream& outf);
int main(){
       cout << "Enter Facile program file name: ";
        string filename;
        getline(cin, filename);
        ifstream infile(filename.c_str());
        if (!infile){
            cout << "Cannot open " << filename << "!" << endl;
            return 1;
        }
        interpretProgram(infile, cout);
}
void parseProgram(istream &inf, vector<Statement *> & program){
	program.push_back(NULL);
	string line;
	while( ! inf.eof() ){
		getline(inf, line);
		program.push_back( parseLine( line ) );
	}
}
Statement * parseLine(string line){
	stringstream ss;
	string type, var, var_second;
	int val = 0;
	ss << line;
	ss >> type;
	if( type == "LET" ){
		ss >> var >> val;
		return new LetStatement(var, val);
	} else if( type == "ADD"){
		ss >> var >> var_second;
		return new AddStatement(var, var_second);
	} else if( type == "MULT"){
		ss >> var >> var_second;
		return new MultStatement(var, var_second);
	} else if( type == "SUBT"){
		ss >> var >> var_second;
		return new SubtStatement(var, var_second);
	} else if( type == "DIV"){
		ss >> var >> var_second;
		return new DivStatement(var, var_second);
	} else if( type == "GOTO"){
		ss >> val;
		return new GotoStatement(val);
	} else if( type == "IF"){
		std::string comp_type;
		ss >> var >> comp_type >> var_second >> val;
		return new IfStatement(var, comp_type, var_second, val);
	} else if( type == "GOSUB"){
		ss >> val;
		return new GosubStatement(val);
	} else if( type == "PRINT"){
		ss >> var;
		return new PrintStatement(var); 
	} else if( type == "PRINTALL") return new PrALLStatement();
	else if( type == "RETURN")	return new RetrStatement();
	else  return new EndStatement();
}
void interpretProgram(istream& inf, ostream& outf){
	vector<Statement *> program;
	parseProgram(inf, program);
	ProgramState* state = new ProgramState(program.size());
	program[1]->execute(state,outf);
	int place = state->Get_Place(), size = program.size();
	while(place != -1 && place < size){
		program[place]->execute(state,outf);
		place = state->Get_Place();
	}
	 for (int i = 1; i < size; ++i)	delete program[i];
	 program.clear();
	 delete state;
}
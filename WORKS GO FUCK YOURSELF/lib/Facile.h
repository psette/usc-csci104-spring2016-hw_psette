#ifndef FACILE
#define FACILE
#include "../Statement.h"
#include "PrALLStatement.h"
#include "LetStatement.h"
#include "AddStatement.h"
#include "SubtStatement.h"
#include "MultStatement.h"
#include "DivStatement.h"
#include "RetrStatement.h"
#include "GotoStatement.h"
#include "GosubStatement.h"
#include "IfStatement.h"
#include "EndStatement.h"
#include "PrintStatement.h"
#include "vec_filler.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream> 
#include <fstream>
#include <cstdlib>
class Facile{
	public:
		Facile(std::string);
		~Facile();
		bool breakpoint(int);
		void parseProgram(std::ifstream &inf);
		Statement*  parseLine(std::string);
		int execute(char);
		void reset();
		std::vector<std::pair<std::string,int> >  getVals();
	private:
		int place, size;
		bool* breakpoints;
		std::vector<Statement *> program;
		ProgramState* state;
};
#endif
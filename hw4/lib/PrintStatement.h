
#ifndef PRINT_STATEMENT_INCLUDED
#define PRINT_STATEMENT_INCLUDED

#include "../Statement.h"
#include <iostream>

class PrintStatement: public Statement
{
private:
	std::string m_variableName;
	
public:
	PrintStatement(std::string);
	
	virtual void execute(ProgramState *, std::ostream &);
};

#endif


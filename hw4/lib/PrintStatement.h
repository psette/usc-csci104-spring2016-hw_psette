#ifndef PRINT_STATEMENT_INCLUDED
#define PRINT_STATEMENT_INCLUDED
#include "../Statement.h"
class PrintStatement: public Statement{
private:
	std::string m_variableName;
	
public:
	PrintStatement(std::string);
	void execute(ProgramState *, std::ostream &);
};

#endif


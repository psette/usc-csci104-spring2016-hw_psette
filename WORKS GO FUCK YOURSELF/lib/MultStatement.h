#ifndef MULT_STATEMENT_INCLUDED
#define MULT_STATEMENT_INCLUDED
#include "../Statement.h"
#include <sstream>
class MultStatement: public Statement{
private:
	std::string m_variableName, value_holder;
	int m_value;
public:
	MultStatement(std::string,  std::string);
	void execute(ProgramState * , std::ostream &);
};

#endif




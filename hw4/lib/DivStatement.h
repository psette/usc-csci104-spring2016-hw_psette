#ifndef DIV_STATEMENT_INCLUDED
#define DIV_STATEMENT_INCLUDED
#include "../Statement.h"
#include <sstream>
class DivStatement: public Statement{
private:
	std::string m_variableName, value_holder;
	int m_value;
public:
	DivStatement(std::string, std::string);
	void execute(ProgramState *, std::ostream &);
};

#endif
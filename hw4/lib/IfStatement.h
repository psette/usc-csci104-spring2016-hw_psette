#ifndef IF_STATEMENT_INCLUDED
#define IF_STATEMENT_INCLUDED
#include "../Statement.h"
#include <sstream>
class IfStatement: public Statement{
private:
	std::string m_variableName, m_comp_type,value_holder;
	int m_value, m_place;
public:
	IfStatement(std::string, std::string, std::string, int);	
	virtual void execute(ProgramState* , std::ostream &);
};
#endif
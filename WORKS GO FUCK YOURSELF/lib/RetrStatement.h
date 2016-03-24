#ifndef RETR_STATEMENT_INCLUDED
#define RETR_STATEMENT_INCLUDED
#include "../Statement.h"
#include <stdexcept>
#include <exception>
class RetrStatement: public Statement{
public:
	RetrStatement();
	void execute(ProgramState *, std::ostream &);
};
#endif
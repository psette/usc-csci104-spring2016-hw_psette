#ifndef RETR_STATEMENT_INCLUDED
#define RETR_STATEMENT_INCLUDED
#include "../Statement.h"
class RetrStatement: public Statement{
public:
	RetrStatement();
	void execute(ProgramState *, std::ostream &);
};
#endif
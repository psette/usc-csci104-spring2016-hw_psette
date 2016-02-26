
#ifndef PRALL_STATEMENT_INCLUDED
#define PRALL_STATEMENT_INCLUDED

#include "../Statement.h"

class PrALLStatement: public Statement
{
public:
	PrALLStatement();
	virtual void execute(ProgramState *, std::ostream &);
};

#endif


#ifndef GOTO_STATEMENT_INCLUDED
#define GOTO_STATEMENT_INCLUDED
#include "../Statement.h"

class GotoStatement: public Statement{
private:
	int m_value;
public:
	GotoStatement(int value);
	virtual void execute(ProgramState * , std::ostream &);
};

#endif
#ifndef END_STATEMENT_INCLUDED
#define END_STATEMENT_INCLUDED
#include "../Statement.h"
class EndStatement: public Statement{
public:
	EndStatement();
	void execute(ProgramState * , std::ostream &);
};
#endif
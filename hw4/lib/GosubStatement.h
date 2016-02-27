#ifndef GOSUB_STATEMENT_INCLUDED
#define GOSUB_STATEMENT_INCLUDED
#include "../Statement.h"
class GosubStatement: public Statement{
private:
	int go_val;
public:
	GosubStatement(int go_val);
	void execute(ProgramState * , std::ostream &outf);
};

#endif
// RetrStatement.cpp:
#include "../lib/RetrStatement.h"
RetrStatement::RetrStatement()
{}
void RetrStatement::execute(ProgramState * state, std::ostream &outf){
	    state -> Set_Place(state -> Stack_Top() + 1);
	    state -> Stack_Pop();
}
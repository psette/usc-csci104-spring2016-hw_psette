// RetrStatement.cpp:
#include "../lib/RetrStatement.h"
RetrStatement::RetrStatement(){}
/*
Returns to line on top of stack and then removes that line
*/    
void RetrStatement::execute(ProgramState * state, std::ostream &outf){
	if(	state->Stack_Empty()	) throw std::logic_error("No GoSub, yet tried to return");
	state -> Set_Place(state -> Stack_Top() + 1);
	state -> Stack_Pop();
}
// GotoStatement.cpp:
#include "../lib/GosubStatement.h"
#include <stdexcept>
#include <exception>
GosubStatement::GosubStatement(int value): go_val( value ) {}
/*
Pushes line number onto stack and if the jump to line does not exsit, throws exception
*/    
void GosubStatement::execute(ProgramState * state, std::ostream &outf){
	if(go_val < 0 || go_val >= state -> Get_Size()) throw std::logic_error("Illegal Jump");
	state -> Stack_Push(state -> Get_Place() );
	state -> Set_Place(go_val);
}
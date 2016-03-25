// EndStatement.cpp:
#include "../lib/EndStatement.h"
EndStatement::EndStatement(){}
void EndStatement::execute(ProgramState * state, std::ostream &outf){
	state -> Set_Place(-1);
}
// LetStatement.cpp:
#include "../lib/LetStatement.h"
LetStatement::LetStatement(std::string variableName, int value): m_variableName( variableName ), m_value( value ){}
// The LetStatement version of execute() should make two changes to the
// state of the program:
//
//    * set the value of the appropriate variable
//    * increment the program counter
void LetStatement::execute(ProgramState * state, std::ostream &outf){
	state -> Map_Setter(m_variableName, m_value);
	state -> Set_Place(state -> Get_Place() + 1);
}
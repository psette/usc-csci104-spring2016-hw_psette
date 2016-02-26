// GotoStatement.cpp:
#include "../lib/GotoStatement.h"
#include <stdexcept>
#include <exception>
GotoStatement::GotoStatement(int value): m_value( value ){}
// The GotoStatement version of execute() should make two changes to the
// state of the program:
//
//    * set the value of the appropriate variable
//    * increment the program counter
void GotoStatement::execute(ProgramState * state, std::ostream &outf){
	if( m_value >= state -> Get_Size() ) throw std::logic_error("Line Jump Invalid");
	state -> Set_Place(m_value);
}
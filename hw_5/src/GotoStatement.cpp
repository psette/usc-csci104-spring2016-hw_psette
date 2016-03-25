// GotoStatement.cpp:
#include "../lib/GotoStatement.h"
#include <stdexcept>
#include <exception>
GotoStatement::GotoStatement(int value): m_value( value ){}
//If the line number is valid, jump to that line*
void GotoStatement::execute(ProgramState * state, std::ostream &outf){
	if(m_value >= state -> Get_Size() || m_value < 0) throw std::logic_error("Line Jump Invalid");
	else state -> Set_Place(m_value);
}
// DivStatement.cpp:
#include "../lib/DivStatement.h"
#include <stdexcept>
#include <exception>
DivStatement::DivStatement(std::string variableName, std::string value): m_variableName( variableName ), value_holder(value)
{}
void DivStatement::execute(ProgramState * state, std::ostream &outf){
	int val = state -> Map_Getter_Int(m_variableName);
	if( ('0' <= value_holder[0] && value_holder[0] <= '9') || value_holder[0] == '-'){
		std::stringstream ss(value_holder);
		ss >> m_value;
	} 	else	m_value = val;
	if(m_value == 0)	throw std::logic_error("Divide by 0");
    state -> Map_Setter(m_variableName, m_value / val);
    state -> Set_Place(state->Get_Place() + 1);
}
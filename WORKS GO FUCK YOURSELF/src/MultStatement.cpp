// MultStatement.cpp:
#include "../lib/MultStatement.h"
using namespace std;

MultStatement::MultStatement(std::string variableName, std::string value): m_variableName( variableName ), value_holder(value)
{}
/*
Determines if the second parameter is a variable or an integer. Multiplies the value to what is at that key.
*/    
void MultStatement::execute(ProgramState * state, ostream &outf){
	if( ('0' <= value_holder[0] && value_holder[0] <= '9') || value_holder[0] == '-'){
		std::stringstream ss(value_holder);
		ss >> m_value;
	} 	else	m_value = state -> Map_Getter_Int(value_holder);
    state -> Map_Setter(m_variableName, state -> Map_Getter_Int(m_variableName) * m_value);
    state -> Set_Place(state->Get_Place() + 1);
}
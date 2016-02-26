// MultStatement.cpp:
#include "../lib/MultStatement.h"
using namespace std;

MultStatement::MultStatement(std::string variableName, std::string value): m_variableName( variableName ), value_holder(value)
{}
// The MultStatement version of execute() should make two changes to the
// state of the program:
//
//    * set the value of the appropriate variable
//    * increment the program counter
void MultStatement::execute(ProgramState * state, ostream &outf){
	int val = state -> Map_Getter_Int(m_variableName);
	if( ('0' <= value_holder[0] && value_holder[0] <= '9') || value_holder[0] == '-'){
		std::stringstream ss(value_holder);
		ss >> m_value;
	} 	else	m_value = val;
    state -> Map_Setter(m_variableName, m_value * val);
    state -> Set_Place(state->Get_Place() + 1);
}
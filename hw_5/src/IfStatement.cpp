// IfStatement.cpp:
#include "../lib/IfStatement.h"
IfStatement::IfStatement(std::string variableName, std::string comp_type, std::string value, int place)
	: m_variableName( variableName ), m_comp_type(comp_type), value_holder( value ),  m_place(place)
{}
//If if statement is true , jump to that line. Otherwise, move place by 1
void IfStatement::execute(ProgramState * state, std::ostream &outf){
	int val = state -> Map_Getter_Int(m_variableName);
	if( ('0' <= value_holder[0] && value_holder[0] <= '9') || value_holder[0] == '-'){
		std::stringstream ss(value_holder);
		ss >> m_value;
	} 	else	m_value = val;
	bool flag = false;
	if( m_comp_type == "=")	flag = (val == m_value);
	else if( m_comp_type == "<") flag = val < m_value;
	else if( m_comp_type == "<=") flag = ((val == m_value) || (val < m_value));
	else if( m_comp_type == ">") flag = val > m_value;
	else if( m_comp_type == ">=") flag = ((val == m_value) || (val > m_value));
	else if( m_comp_type == "<>") flag = (val != m_value);
	state -> Set_Place( flag ? m_place : state -> Get_Place() + 1);
}
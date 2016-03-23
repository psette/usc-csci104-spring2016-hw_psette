// PrintStatement.cpp:
#include "../lib/PrintStatement.h"

PrintStatement::PrintStatement(std::string variableName): m_variableName( variableName ){}
void PrintStatement::execute(ProgramState * state, std::ostream &outf){
	outf << state -> Map_Getter_Int(m_variableName) <<std::endl;
	state -> Set_Place(state->Get_Place() + 1);
}
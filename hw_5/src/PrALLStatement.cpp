// PrALLStatement.cpp:
#include "../lib/PrALLStatement.h"
PrALLStatement::PrALLStatement(){}
/*
Iterates through map and prints all keys and values
*/    
void PrALLStatement::execute(ProgramState * state, std::ostream &outf){
	for(std::map<std::string,int>::iterator it = state -> map_begin(); it != state -> map_end(); ++it)
		outf << it->first <<" "<<it -> second <<std::endl;
	state -> Set_Place(state->Get_Place() + 1);
}
// PrALLStatement.cpp:
#include "../lib/vec_filler.h"
vec_filler::vec_filler(){}
/*
Iterates through map and prints all keys and values
*/
void vec_filler::execute(ProgramState*  state, std::ostream &outf){}
std::vector<std::pair<std::string,int> > vec_filler::filler(ProgramState * state){
	std::vector<std::pair<std::string,int> > return_vec;
	for(std::map<std::string,int>::iterator it = state -> map_begin(); it != state -> map_end(); ++it){
		return_vec.push_back(std::make_pair(it->first, it->second));
	}    return return_vec;
}
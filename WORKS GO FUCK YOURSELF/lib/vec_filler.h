
#ifndef VEC_FILLER_INCLUDED
#define VEC_FILLER_INCLUDED

#include "../Statement.h"
#include <vector>

class vec_filler: public Statement
{
public:
	vec_filler();
	void execute(ProgramState *, std::ostream &);
	std::vector<std::pair<std::string,int> > filler(ProgramState*);
};
#endif
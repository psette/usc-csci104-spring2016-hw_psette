// AddStatement.h
//
// CS 104 / Spring 2016
//
// The AddStatement class encapsulates a LET statement in a Facile program.
// A LET statement looks like this:
//
//     LET A 3
//
// Primarily, it consists of two things: a variable name and an integer value.  
// So, a AddStatement object contains a string and an integer, which is the 
// important information contained in a LET statement.
//
// You'll need to similarly define subclasses for each of the other kinds of
// statements in a Facile program.
#ifndef ADD_STATEMENT_INCLUDED
#define ADD_STATEMENT_INCLUDED
#include "../Statement.h"
#include <sstream>
class AddStatement: public Statement{
private:
	std::string m_variableName, value_holder;
	int m_value;
public:
	AddStatement(std::string, std::string);
	virtual void execute(ProgramState* , std::ostream &);
};

#endif




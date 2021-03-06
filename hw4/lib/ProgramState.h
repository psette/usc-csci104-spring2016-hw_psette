// ProgramState.h
//
// CS 104 / Spring 2016
//
// The ProgramState class encapsulates the state of an executing Facile
// program.  The state of a Facile program consists of three parts:
//
//    * The program counter, which specifies the line number of the
//      statement that will execute next.
//    * A map, as explained by the problem writeup.
//    * A stack of integers, which is used to hold return lines for GOSUB
//      statements.
//
// I've provided you a start on this class, but you'll need to add methods
// to it as you go along.  In particular, you'll need methods to access and
// modify the state; these methods will be called primarily by the various
// execute() methods in the Statement subclasses, to allow the execution of
// a statement to change the state of a program.  For example, executing a
// GOTO statement will cause the program counter to be changed.

#ifndef PROGRAM_STATE_INCLUDED
#define PROGRAM_STATE_INCLUDED
#include "stackint.h"
#include <map>
#include <string>

class ProgramState{
public:
	ProgramState(int);
	~ProgramState();
	int Get_Size();
	void Map_Setter(std::string, int);
	int Map_Getter_Int(std::string);
	void Stack_Push(int);
	void Stack_Pop();
	int Stack_Top();
	void Set_Place(int);
	int Get_Place();
	int Get_Line_Num();
	std::map<std::string, int>::iterator map_begin();
	std::map<std::string, int>::iterator map_end();
private:
	int size, Place;
	std::map<std::string, int> variable_map;
	StackInt stack;
};

#endif
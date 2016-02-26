#include "../lib/ProgramState.h"
#include <stdexcept>
#include <exception>
ProgramState::ProgramState(int value):size(value) , Place(1) {}
ProgramState::~ProgramState(){
	variable_map.clear();
}
int ProgramState::Get_Size(){
	return size;
}
void ProgramState::Map_Setter(std::string input, int val){
	variable_map[input] = val;
}
int ProgramState::Map_Getter_Int(std::string input){
	std::map<std::string, int>::iterator it = variable_map.find(input);
	return it == variable_map.end() ? 0 : it -> second;
}
void ProgramState::Stack_Push(int val){
	stack.push(val);
}
bool ProgramState::Stack_Empty(){
	return stack.empty();
}
int ProgramState::Stack_Top(){
	return stack.top();
}
void ProgramState::Stack_Pop(){
	stack.pop();
}
void ProgramState::Set_Place(int mod_place){
	Place = mod_place;
}
int ProgramState::Get_Place(){
	return Place;
}
std::map<std::string, int>::iterator ProgramState::map_begin(){
	return variable_map.begin();
}
std::map<std::string, int>::iterator ProgramState::map_end(){
	return variable_map.end();
}
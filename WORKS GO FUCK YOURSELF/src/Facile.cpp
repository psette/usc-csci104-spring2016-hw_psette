// Facile.cpp
#include "../lib/Facile.h"
using namespace std;
Facile::Facile(string filename){
	ifstream infile(filename.c_str());
	if (!infile){
		cout << "Cannot open " << filename << "!" << endl;
		return;
	}
	parseProgram(infile);
	state = new ProgramState(program.size());
	breakpoints = new bool[size];
	for(int i = 0; i < size; i++)		breakpoints[i] = false;
	place = 1;
}
Facile::~Facile(){
	delete [] breakpoints;
	for (int i = 1; i < size; ++i)	delete program[i];
	program.clear();
	delete state;
}
bool Facile::breakpoint(int breakplace, bool just_checking){
	if(just_checking)	return breakpoints[breakplace];
	if(true == breakpoints[breakplace])	return true;
	breakpoints[breakplace] = true;
	return false;
}
void Facile::parseProgram(ifstream &inf){
	program.push_back(NULL);
	string line;
	while( ! inf.eof() ){
		getline(inf, line);
		program.push_back( parseLine( line ) );
	}
	size = program.size();
}
Statement* Facile::parseLine(string line){
	stringstream ss;
	string type, var, var_second;
	int val = 0;
	ss << line;
	ss >> type;
	if( type == "LET" ){
		ss >> var >> val;
		return new LetStatement(var, val);
	} else if( type == "ADD"){
		ss >> var >> var_second;
		return new AddStatement(var, var_second);
	} else if( type == "MULT"){
		ss >> var >> var_second;
		return new MultStatement(var, var_second);
	} else if( type == "SUB"){
		ss >> var >> var_second;
		return new SubtStatement(var, var_second);
	} else if( type == "DIV"){
		ss >> var >> var_second;
		return new DivStatement(var, var_second);
	} else if( type == "GOTO"){
		ss >> val;
		return new GotoStatement(val);
	} else if( type == "IF"){
		std::string comp_type, dummy;
		ss >> var >> comp_type >> var_second >> dummy>> val;
		return new IfStatement(var, comp_type, var_second, val);
	} else if( type == "GOSUB"){
		ss >> val;
		return new GosubStatement(val);
	} else if( type == "PRINT"){
		ss >> var;
		return new PrintStatement(var); 
	} else if( type == "PRINTALL") return new PrALLStatement();
	else if( type == "RETURN")	return new RetrStatement();
	else  return new EndStatement();
}
std::vector<std::pair<std::string,int> >  Facile::getVals(){
	std::vector<std::pair<std::string,int> > return_vec;
	vec_filler temp;
	return_vec = temp.filler(state);
	return return_vec;
}
int Facile::execute(char type){
	breakpoints[place] = false;
	if(type == 's'){
		program[place]->execute(state,cout);
	}else if(type == 'n'){
		while(place != -1 && place < size && !breakpoints[place] ){
			program[place]->execute(state,cout);
			place = state->Get_Place();
			if(state->Stack_Empty() ) break;
		}
	}else{
		while(place != -1 && place < size && !breakpoints[place]){
			program[place]->execute(state,cout);
			place = state->Get_Place();
		}
	}
	place = state->Get_Place();
	return place == -1 ? -42 : place;
}
void Facile::reset(){
	place = 1;
	delete state;
	state = new ProgramState(program.size());
	for(int i = 0; i < size; i++)		breakpoints[i] = false;
}
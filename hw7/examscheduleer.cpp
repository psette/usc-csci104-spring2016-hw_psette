#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <map>
bool isValid(std::map<std::string,std::vector<int> >& classMap, std::map<int,int>& slotMap){
	for(std::map<std::string,std::vector<int> >::iterator it = classMap.begin(); it!= classMap.end(); ++it){
		for(unsigned i = 0; i < it -> second.size(); ++i){
			for(unsigned j= 0; j < it -> second.size(); ++j){
				if(slotMap[(it->second)[i]] == slotMap[(it->second)[j]] && i != j && slotMap[(it->second)[i]] != 0 )
					return false;
			}
		}
	}
	return true;
}
bool solveHelper(std::map<std::string,std::vector<int> >& classMap, std::map<int,int>& slotMap, const std::string& element, std::vector<int>& classesvec, const int& index, const int& num_slots){
	if(index == classesvec.size())	return true;
	std::map<std::string,std::vector<int> >::iterator it = classMap.find(element);
	if( index > it->second.size() )
		if(++it == classMap.end() ) return true;
	for(int i = 0; i < num_slots; ++i){
		slotMap[ classesvec[index] ] = i + 1;
		if( isValid(classMap,slotMap) )
			if(solveHelper(classMap,slotMap,it->first,classesvec, index + 1, num_slots)) return true;
	}
	return false;
}
int main(int argc, char* argv[]){
	int num_exams = -1, num_students = -1, num_slots = -1, temp_class = 0;
	std::ifstream input(argv[1]);
	std::string temp;
	input >> num_exams >> num_students >> num_slots;
	if(num_slots < 0 || num_exams < 0 || num_students < 0){
		std::cerr<< "Check input"<<std::endl;
		return -1;
	}
	std::map<std::string,std::vector<int> > classMap;
	std::map<int,int> slotMap;
	std::vector<int> classesvec;
	while(getline(input, temp)) {
		bool isThere = false;
		std::stringstream ss;
		std::string student;
		ss << temp;
		ss >> student;
		std::vector<int> vec;
		while(ss >> temp_class)	{
			for(int i = 0; i < classesvec.size(); i++){
				if(classesvec[i] == temp_class)
					isThere = true; break;
			}
			if(!isThere) classesvec.push_back(temp_class);
			vec.push_back(temp_class);
		}
		classMap[student]= vec;
	}
	if(solveHelper(classMap, slotMap, classMap.begin()->first, classesvec, 0, num_slots)){
		for(std::map<int,int>::iterator it = slotMap.begin(); it != slotMap.end(); ++it)
			std::cout<<it->first<<"\t"<<it->second<<std::endl;
	} else
		std::cout<<"No Solution"<<std::endl;
	return 0;
}
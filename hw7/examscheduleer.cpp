#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
int main(int argc, char* argv[]){
	int num_exams = -1, num_students = -1, num_slots = -1;
	if(argc < 3){
	std::cerr << "Please provide an input and output file." << std::endl;
	return -1;
	}
	ifstream input(argv[1]);
	std::string temp;
	if(getline(input,temp)){
		stringstream ss;
		ss << temp;
		ss >> num_exams;
		ss >> num_students;
		ss > num_slots;
	}
	if(num_slots < 0 || num_exams < 0 || num_students < 0){
		std::cerr<< "Negative values"<<std::endl;
		return -1;
	}
	std::vector<std::string> *vec = std::vector<std::string>[num_class] ;
	int * num_class = new int[num_exams], temp_class = 0, class_counter = 0;
	while(getline(input, temp)) {
		bool isThere = false;
		stringstream ss;
		std::string student;
		ss << temp;
		ss >> student;
		while(ss >> temp_class){
			bool isThere = false;
			for(int i = 0; i <= class_counter; i++){
				if(num_class[i] == temp_class){
					vec[i].push_back(student);
						isThere = true;
				}
			}
			if(!isThere){
				vec[++class_counter].push_back(student);
			}
		}
	}

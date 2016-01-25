#include <iostream>
#include <fstream>
int main(int argc, char *argv[]){
	if(argc != 2){	
		std::cerr<<"Check Inputs"<<std::endl;
		return -1;
	}
	std::string filename = argv[1];
	std::ifstream file(filename);
	if(file.fail())	std::cerr<< "Check FileName" <<std::endl;
	int num = 0;
	file >> num;
	std::string* words =  new std::string[num];
	for(int i = num - 1; i >= 0; i--) file >> words[i];
	for(int i = 0; i < num; i++) std::cout<< words[i] <<std::endl;
	delete [] words;
	return 0;
}

#include "hashtable.h"
#include "splaytree.h"
#include <vector>
#include <ctime>
#include <fstream>
int main (int argc, char *argv[]){
	char * tempa = argv[1];
	std::ifstream input(tempa);
	std::ifstream input2(tempa);
	clock_t start;
	int num = argv[2][0] -'0';
	if(argc != 3 || (num != 4 && num != 5) ){
		std::cerr<<"Check Input"<<std::endl;
		return -1;
	}
	std::string temp;
	HashTable hash;
	SplayTree<std::string,int> splay;
	start = clock();
	while(input>>temp)	hash.add(temp);
	double hashTime = (clock() - start ) / (double) CLOCKS_PER_SEC;
	start = clock();
	std::cerr<<hashTime;
	temp ="";
	while(input2>>temp)	splay.add(temp);
	double splayTime = (clock() - start ) / (double) CLOCKS_PER_SEC;
	hash.reportAll(std::cout);
	std::cout<<"HASH TIME: "<<hashTime<<std::endl;
	std::cout<<"SPLAY TIME: "<<splayTime<<std::endl;
	if(splayTime > hashTime) std::cout<<"HashTable FASTER BY: "<<splayTime - hashTime<<std::endl;
	else std::cout<<"SplayTree FASTER BY: "<<hashTime - splayTime<<std::endl;
	return 0;
}
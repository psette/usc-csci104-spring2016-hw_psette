#include "hashtable.h"
#include "splaytree.h"
#include <ctime>
#include <fstream>
int main (int argc, char *argv[]){
	char * tempa = argv[2];
	std::ifstream input(tempa);
	std::ifstream input2(tempa);
	int num = argv[1][0] -'0';
	if(argc != 3 || (num != 4 && num != 5) ){
		std::cerr<<"Check Input"<<std::endl;
		return -1;
	}
	std::string temp;
	SplayTree<std::string,int> splay;
	clock_t start = clock();
	if(num == 4){
		HashTable hash;
		while(input >> temp) hash.add(temp);
		hash.reportAll(std::cout);
		std::cout<<"HASH TIME: "<< (clock() - start ) / (double) CLOCKS_PER_SEC<<" seconds."<<std::endl;

	}	else {
		SplayTree<std::string,int> splay;
		while(input2>>temp)	splay.add(temp);
		splay.reportAll(std::cout);
		std::cout<<"SPLAY TIME: "<<(clock() - start ) / (double) CLOCKS_PER_SEC<<" seconds."<<std::endl;

	}
	return 0;
}
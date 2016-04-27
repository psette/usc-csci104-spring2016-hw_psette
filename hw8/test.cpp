#include "hashtable.h"
#include "splaytree.h"
#include <vector>
#include <ctime>
#include <fstream>
std::vector<std::string> vec;
void permute(std::string a, int i=0){
if (i == a.size()-1)vec.push_back(a);
else{
   for(int j=i; j<a.size(); j++){
      std::swap(a[i], a[j]);   
      permute(a, i+1);
      std::swap(a[i], a[j]);
}
}
}
int main (int argc, char *argv[]){
	std::ifstream input(argv[1]);
	int num = argv[2][0] -'0';
	if(argc != 3 || (num != 4 && num != 5) ){
		std::cerr<<"Check Input"<<std::endl;
		return -1;
	}
	std::string temp;
	HashTable hash;
	SplayTree<std::string,int> splay;
	while(num == 4 && input>>temp){
		hash.add(temp);
	}
	while(num == 5 && input>>temp){
		splay.add(temp);
	}
	hash.reportAll(std::cout);
	splay.reportAll(std::cout);

	return 0;
}

/*
 	clock_t start;
    double duration;
    start = clock();
	HashTable table;
	SplayTree<std::string,int> tree;
	permute("abcdefg");
	for(int i = 0; i < vec.size();i++) table.add(vec[i]);
	//table.reportAll(std::cout);
	double hashTime = (clock() - start ) / (double) CLOCKS_PER_SEC;
	start = clock();
	for(int i = 0; i < vec.size();i++) {
		tree.add(vec[i]);
	}
	double splayTime = (clock() - start ) / (double) CLOCKS_PER_SEC;
	//tree.reportAll(std::cout);
	if(splayTime > hashTime) std::cout<<"HashTable FASTER BY: "<<splayTime - hashTime<<std::endl;
	else std::cout<<"SplayTree FASTER BY: "<<hashTime - splayTime<<std::endl;
}
*/
#include <iostream>
#include <utility>
#include <stdlib.h>
#include <time.h>

#include "avlbst.h"


int main()
{
	AVLTree<int, int> avl;
	avl.insert(std::make_pair(20,2));
	avl.insert(std::make_pair(10,2));
	avl.insert(std::make_pair(30,2));
	avl.insert(std::make_pair(3,2));
	avl.insert(std::make_pair(1,2));

/*
	avl.insert(std::make_pair(2,2));
	avl.insert(std::make_pair(3,3));
	avl.insert(std::make_pair(4,4));
	avl.insert(std::make_pair(4,4));
	avl.insert(std::make_pair(3321,3));
	avl.insert(std::make_pair(12342,2));
	avl.insert(std::make_pair(2311,1));
	avl.remove(2311);
	*/
	avl.remove(10);
	std::cout << "********* Printing Inorder Now *********" << std::endl;
	avl.print();
	//for(AVLTree<int,int>::iterator it = avl.begin(); it != avl.end(); ++it)
	//	std::cerr<<it->first<<std::endl;




	return 0;
}
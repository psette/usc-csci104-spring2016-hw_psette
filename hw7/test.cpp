#include <iostream>
#include <utility>
#include <stdlib.h>
#include <time.h>

#include "avlbst.h"
#include "bst.h"


int main()
{
	AVLTree<int, int> avl;

	/*
	avl.insert(std::make_pair(2,2));
	avl.insert(std::make_pair(3,3));
	avl.insert(std::make_pair(4,4));
	*/
	// avl.insert(std::make_pair(5,5));
	avl.insert(std::make_pair(4,4));
	avl.insert(std::make_pair(3,3));
	avl.insert(std::make_pair(2,2));
	avl.insert(std::make_pair(1,1));


	/*
	srand(time(NULL));
	int insert;

	for(int i = 0; i < 20; i++)
	{
		insert = rand() % 1000;
		// std::cout << insert << std::endl;
		avl.insert(std::make_pair(insert, 1));
	}
	*/	

	std::cout << "********* Printing Inorder Now *********" << std::endl;
	std:: cout << std::endl;

	for(AVLTree<int, int>::iterator it = avl.begin(); it != avl.end(); ++it)
	{
		// do something
		std::cout << it->first << std::endl;
	}
	




	return 0;
}
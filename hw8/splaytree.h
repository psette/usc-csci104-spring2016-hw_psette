#include "Map.h"
#include "bst.h"
#include <sstream> 
template <class KeyType, class ValueType>
class SplayTree : public BinarySearchTree<KeyType, ValueType>, public Map{
  public:
  	SplayTree(){};	//constructor
  	~SplayTree(){};	//destructor
  	void add(const std::string& word){	// add function calls insert
  		insert(std::make_pair(word,1));	
  	}
  	void reportAll(std::ostream& output){	//report all uses the BST iterator and inorder prints everything
  		if(this->root == NULL) return;	//catches if theres nothing in it
  		for (SplayTree<std::string, int>::iterator it = this->begin(); it != this->end(); ++it)
			output << (*it).first << " " << (*it).second << "\n";
  	}
  private:
    void insert(const std::pair<const KeyType, ValueType>& new_item) {	//Private insert
		Node<KeyType, ValueType>* find = this->internalFind(new_item.first);	//finds the value
		if(this->root == NULL){	//if empty, set root to Val
			Node<KeyType, ValueType>* new_Node = new Node<KeyType, ValueType>( new_item.first, new_item.second, NULL);
			this->root = new_Node;
	    }	else if(find != NULL){	//if found
			find->setValue(find->getValue() + 1);	//increments the value
			splay(find);	//splays
		}	else	insertHelper((this->root), new_item);	
    }

    void insertHelper(Node<KeyType, ValueType>* node,const std::pair<const KeyType, ValueType>& item){
		if(item.first > node->getKey()){	//if greater than current node
			if(node->getRight() == NULL){	//if right child null, insert and splay
				Node<KeyType, ValueType>* new_Node = new Node<KeyType, ValueType>(item.first,item.second,node);
				node->setRight(new_Node);
				splay(new_Node);
			} 	else insertHelper(node->getRight(), item);	// otherwise call on right child
		}	else	{
			if(node->getLeft() == NULL){	//If left child null, insert and splay
				Node<KeyType, ValueType>* new_Node = new Node<KeyType, ValueType>(item.first,item.second,node);
				node->setLeft(new_Node);
				splay(new_Node);
        	}	else insertHelper(node->getLeft(), item);	//call on left child
		}
	}
    void splay(Node<KeyType, ValueType>* x){	//splay
		Node<KeyType, ValueType> *p = x->getParent();	//save parent	
		if(x == NULL || p == NULL)	return;			//If node or parent are null, return
		Node<KeyType, ValueType>* g = p->getParent(), *left = x->getLeft(), *right = x->getRight(), *temp;
		if (g == NULL && p != NULL){	//if grandparent is null and parent is not
			this->root = x;	x->setParent(NULL);	//set x as root
			if (p->getRight() == x){		//if x is right child
				if (left != NULL)	left->setParent(p);	//if leftchild is not null, set p as the parent
				x->setLeft(p);							//set parent and children
				p->setParent(x);	p->setRight(left);

			}	else {					//if x is left child
				if (right != NULL)	right->setParent(p);	//if rightchild is not null, set p as parent
				x->setRight(p);							//set parent and children
				p->setParent(x);	p->setLeft(right);
			}
		}
		bool root_node = g != NULL && g->getParent() == NULL;
		/*	follow one of the cases gone over in class */
		if (p != NULL && g != NULL && p->getLeft() == x && g->getLeft() == p){
			if (root_node)	this->root = x;
			else	g->getParent()->getRight() == g ? g->getParent()->setRight(x): g->getParent()->setLeft(x);
	   	  	if (right != NULL)	right->setParent(p);
			temp = p->getRight();
			if (temp != NULL)	temp->setParent(g);
			x->setParent(g->getParent());	x->setRight(p);
			p->setParent(x);	p->setLeft(right);p->setRight(g);
			g->setParent(p);	g->setLeft(temp);
		} else if (p != NULL && g != NULL && p->getRight() == x && g->getRight() == p){
			if (root_node)	this->root = x;
			else g->getParent()->getRight() == g ? g->getParent()->setRight(x): g->getParent()->setLeft(x);
			temp = p->getLeft();
			if (left != NULL)	left->setParent(p);	if (temp != NULL)	temp->setParent(g);
			x->setParent(g->getParent());	x->setLeft(p);
			p->setParent(x);	p->setRight(left);	p->setLeft(g);
			g->setParent(p);	g->setRight(temp);
   	  	}
		if (p != NULL && g != NULL && p->getRight() == x && g->getLeft() == p){
	   	  	if (root_node)	this->root = x;
			else	g->getParent()->getRight() == g ? g->getParent()->setRight(x): g->getParent()->setLeft(x);
			if (left != NULL)		left->setParent(p);
	   	  	if (right != NULL)		right->setParent(g);
			x->setParent(g->getParent());	x->setRight(g);	x->setLeft(p);
			g->setParent(x);	g->setLeft(right);
			p->setParent(x);	p->setRight(left);
		}	else if (p != NULL && g != NULL && p->getLeft() == x && g->getRight() == p){
			if (root_node)	this->root = x;
			else	g->getParent()->getRight() == g ? g->getParent()->setRight(x): g->getParent()->setLeft(x);
			if (right != NULL)	right->setParent(p);
			if (left != NULL)	left->setParent(g);
			x->setParent(g->getParent());	x->setRight(p);	x->setLeft(g);
			p->setParent(x);	p->setLeft(right);
			g->setParent(x);	g->setRight(left);
		}
		splay(x); //recursivley call, splay up the tree
	}
};
#include "Map.h"
#include "bst.h"
#include <sstream> 
template <class KeyType, class ValueType>
class SplayTree : public BinarySearchTree<KeyType, ValueType>, public Map{
  public:
  	void add(const std::string& word){
  		insert(std::make_pair(word,1));
  	}
  	void reportAll(std::ostream& output){
  		if(this->root == NULL) return;
  		for (SplayTree<std::string, int>::iterator it = this->begin(); it != this->end(); ++it)
			output << (*it).first << " " << (*it).second << "\n";
  	}
  private:
    void insert(const std::pair<const KeyType, ValueType>& new_item) {
		Node<KeyType, ValueType>* find = this->internalFind(new_item.first);
		if(find != NULL){
			find->setValue(find->getValue() + 1);
			splay(find);
			return;
		}	else if(this->root == NULL){
			Node<KeyType, ValueType>* new_Node = new Node<KeyType, ValueType>( new_item.first, new_item.second, NULL);
			this->root = new_Node;
	    }	else	insertHelper((this->root), new_item);
    }

    void insertHelper(Node<KeyType, ValueType>* node,const std::pair<const KeyType, ValueType>& item){
		if(item.first < node->getKey()){
			if(node->getLeft() != NULL)	insertHelper(node->getLeft(), item);
        	else{
				Node<KeyType, ValueType>* new_Node = new Node<KeyType, ValueType>(item.first,item.second,node);
				node->setLeft(new_Node);
				splay(new_Node);
        	}
		}	else	{
	        	if(node->getRight() != NULL)	insertHelper(node->getRight(), item);
	        	else{
					Node<KeyType, ValueType>* new_Node = new Node<KeyType, ValueType>(item.first,item.second,node);
					node->setRight(new_Node);
					splay(new_Node);
				} 
		}
	}
    void splay(Node<KeyType, ValueType>* x){
		Node<KeyType, ValueType>* head = x, *p = x->getParent();
		if(head == NULL || p == NULL)	return;
		Node<KeyType, ValueType>* g = p->getParent(), *left = x->getLeft(), *right = x->getRight(), *temp;
		if (g == NULL && p != NULL){
			this->root = x;
			x->setParent(NULL);
			if (p->getLeft() == x){
				x->setRight(p);
				p->setParent(x);
				p->setLeft(right);
				if (right != NULL)	right->setParent(p);
			}	else {
				x->setLeft(p);
				p->setParent(x);
				p->setRight(left);
				if (left != NULL)	left->setParent(p);
			}
		}
		bool isRoot = (g != NULL && g->getParent() == NULL);
		if (p != NULL && g != NULL && p->getLeft() == x && g->getLeft() == p){
			if (isRoot)	this->root = x;
			else	g->getParent()->getRight() == g ? g->getParent()->setRight(x): g->getParent()->setLeft(x);
			x->setParent(g->getParent());
			temp = p->getRight();
			x->setRight(p);
			p->setParent(x);
			p->setLeft(right);
	   	  	if (right != NULL)	right->setParent(p);
			p->setRight(g);
			g->setParent(p);
			g->setLeft(temp);
			if (temp != NULL)	temp->setParent(g);
		} else if (p != NULL && g != NULL && p->getRight() == x && g->getRight() == p){
			if (isRoot)	this->root = x;
			else g->getParent()->getRight() == g ? g->getParent()->setRight(x): g->getParent()->setLeft(x);
			x->setParent(g->getParent());
			temp = p->getLeft();
			x->setLeft(p);
			p->setParent(x);
			p->setRight(left);
			if (left != NULL)	left->setParent(p);
			p->setLeft(g);
			g->setParent(p);
			g->setRight(temp);
			if (temp != NULL)	temp->setParent(g);
   	  	}
		right = x->getLeft();
		temp = x->getRight();
		if (p != NULL && g != NULL && p->getRight() == x && g->getLeft() == p){
	   	  	if (isRoot)	this->root = x;
			else	g->getParent()->getRight() == g ? g->getParent()->setRight(x): g->getParent()->setLeft(x);
			x->setParent(g->getParent());
			x->setRight(g);
			g->setParent(x);
			x->setLeft(p);
			p->setParent(x);
			p->setRight(right);
			if (right != NULL)		right->setParent(p);
	   	  	g->setLeft(temp);
	   	  	if (temp != NULL)		temp->setParent(g);
		}	else if (p != NULL && g != NULL && p->getLeft() == x && g->getRight() == p){
			if (isRoot)	this->root = x;
			else	g->getParent()->getRight() == g ? g->getParent()->setRight(x): g->getParent()->setLeft(x);
			x->setParent(g->getParent());
			x->setRight(p);
			p->setParent(x);
			x->setLeft(g);
			g->setParent(x);
	   	  	p->setLeft(temp);
			if (temp != NULL)	temp->setParent(p);
			g->setRight(right);
			if (right != NULL)	right->setParent(g);
		}
		splay(x);
	}
};
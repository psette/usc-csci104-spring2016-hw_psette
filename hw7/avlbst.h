//avlbst.h
#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <stdexcept>
#include <exception>
#include <cstdlib>
#include "bst.h"

template <class KeyType, class ValueType>
class AVLNode : public Node<KeyType, ValueType>
{
public:
  AVLNode (KeyType k, ValueType v, AVLNode<KeyType, ValueType> *p)
    : Node<KeyType, ValueType> (k, v, p)
    { height = 0; }
  
  virtual ~AVLNode () {}
  
  int getHeight () const
    { return height; }
  
  void setHeight (int h)
    { height = h; }
  
  virtual AVLNode<KeyType, ValueType> *getParent () const
    { return (AVLNode<KeyType,ValueType>*) this->_parent; }
  
  virtual AVLNode<KeyType, ValueType> *getLeft () const
    { return (AVLNode<KeyType,ValueType>*) this->_left; }
  
  virtual AVLNode<KeyType, ValueType> *getRight () const
    { return (AVLNode<KeyType,ValueType>*) this->_right; }
  
 protected:
  int height;
};

/* -----------------------------------------------------
 * AVL Search Tree
 ------------------------------------------------------*/

template <class KeyType, class ValueType>
class AVLTree : public BinarySearchTree<KeyType, ValueType>
{
public:
    void print(){printhelper(static_cast<AVLNode<KeyType,ValueType>*>(this->root));}
    void printhelper(AVLNode<KeyType, ValueType>* Root){
    if(Root != NULL){
        printhelper(Root->getLeft());
        std::cerr << Root->getKey() << std::endl;
        printhelper(Root->getRight());
    }
}
   AVLNode<KeyType, ValueType>* find(const KeyType& k) const {
    AVLNode<KeyType, ValueType> *curr = static_cast<AVLNode<KeyType,ValueType>*>(this->root);
    while (curr) {
      if (curr->getKey() == k) return curr;
      else if (k < curr->getKey()) curr = curr->getLeft();
      else curr = curr->getRight();
    }
    return NULL;
  }
  void insert (const std::pair<const KeyType, ValueType>& new_item){
    if(find(new_item.first) != NULL) return;
    insertHelper(static_cast<AVLNode<KeyType,ValueType>*>(this->root),new_item,static_cast<AVLNode<KeyType,ValueType>*>(this->root));
  }
  void remove (const KeyType &toRemove){
   try{
      removeHelper(static_cast<AVLNode<KeyType,ValueType>*>(this->root),toRemove);
    }catch (std::logic_error& e){
      std::cerr<<"ERROR"<<std::endl;
    }

  }
private:
  AVLNode<KeyType, ValueType>* insertHelper(AVLNode<KeyType, ValueType>* node, const std::pair<const KeyType, ValueType>& new_item, AVLNode<KeyType, ValueType>* parent){
    if(node == NULL){
      AVLNode<KeyType, ValueType>* inserting = new AVLNode<KeyType, ValueType>(new_item.first,new_item.second, parent);
      inserting -> setRight(NULL);
      inserting -> setLeft(NULL);
      inserting -> setParent(parent);
      if(this -> root == NULL){
        this -> root = inserting;
        inserting->setHeight(0);
      }
      else if(hasSibiling(inserting)) HeightSetter(inserting); 
      else inserting->setHeight(0);
      return inserting;
    }
    if(new_item.first > node->getKey()) node -> setRight(insertHelper(node->getRight(), new_item, node));
    if(new_item.first < node->getKey()) node -> setLeft(insertHelper(node->getLeft(), new_item, node));
    return node;
  }
  bool hasSibiling(AVLNode<KeyType, ValueType>* node){
    AVLNode<KeyType, ValueType>* parent = node ->getParent();
    return parent != NULL && parent-> getLeft() == node ? parent -> getRight() != NULL : parent -> getLeft() != NULL;
  }
  void SetBalanceAndHeights(AVLNode<KeyType, ValueType>* node, bool deleting = false ){
    if(deleting)  {
      std::cerr<<"DELETEING SET BALCANCE";
      HeightHelper(node);
      return;
    }
    if(node -> getParent() == NULL ) return;
    if(!hasSibiling(node) ){
      while(node -> getParent() != NULL){
        HeightHelper(node);
        node = node -> getParent();
      }
    }
  }
  void removeHelper(AVLNode<KeyType, ValueType>* node, const KeyType& value){
    if(node == NULL) throw std::logic_error("Not in Tree");
    else if(node -> getKey() == value) {
      AVLNode<KeyType, ValueType>* parent = node -> getParent();
      if(parent == NULL){
        std::cerr<<"ISROOT"<<std::endl;
        if(node -> getLeft() == NULL && node-> getRight() == NULL) {
          std::cerr<<"hasnochildren"<<std::endl;
          delete node; 
          this->root = NULL;
        } else if(node->getLeft() == NULL|| node ->getRight() == NULL){
          std::cerr<<"has1child"<<std::endl;
          this -> root = node -> getRight() == NULL ? node -> getLeft() : node -> getRight();
          this -> root -> setParent(NULL);
          delete node;
          SetBalanceAndHeights(static_cast<AVLNode<KeyType,ValueType>*>(this->root),true);
        } else{
          std::cerr<<"haschildren"<<std::endl;
          AVLNode<KeyType, ValueType>* switch_to = node -> getLeft(), *temp = NULL;
          while( switch_to -> getRight() != NULL) switch_to = switch_to -> getRight();
          std::cerr<<switch_to->getKey();
          temp = switch_to -> getParent();
          temp -> getRight() == node ? temp -> setRight(NULL) : temp->setLeft(NULL);
          switch_to ->setParent(NULL);
          switch_to -> setLeft(node->getLeft());
          switch_to -> setRight(node->getRight());
          node -> getLeft() -> setParent(switch_to);
          std::cerr<<"after opeatioins";
          node -> getRight() -> setParent(switch_to);
          this->root = switch_to;
          delete node;
          SetBalanceAndHeights(temp,true);
        }
      }else if ((node->getLeft() == NULL) && (node->getRight() == NULL)){
        parent -> getLeft() == node ? parent -> setLeft(NULL) : parent ->setRight(NULL);
        delete node;
        SetBalanceAndHeights(node);
      } else if( node -> getRight() == NULL){
          AVLNode<KeyType, ValueType>* left = node ->getLeft();
          parent -> getRight() == node ? parent -> setRight(node->getLeft()) : parent ->setLeft(node -> getLeft());
          node->getLeft()->setParent(parent);
          delete node;
          SetBalanceAndHeights(left);
      } else if(node -> getLeft() == NULL){
          AVLNode<KeyType, ValueType>* right = parent -> getRight();
          parent -> getLeft() == node ? parent -> setLeft(node->getRight()) : parent ->setRight(node -> getRight());
          node->getRight()->setParent(parent);
          delete node;
          SetBalanceAndHeights(right);
      } else {
        AVLNode<KeyType, ValueType>* switch_to = node -> getLeft(), *temp = NULL;
        while(switch_to -> getRight() != NULL) switch_to = switch_to -> getRight();
          temp = switch_to -> getParent();
          switch_to ->setParent(parent);
          switch_to -> setLeft(node->getLeft());
          switch_to -> setRight(node->getRight());
          switch_to -> getLeft() -> setParent(switch_to);
          switch_to -> getRight() -> setParent(switch_to);
          delete node;
          SetBalanceAndHeights(temp);      
      }
    } else removeHelper(node -> getKey() > value ? node -> getLeft() : node -> getRight(), value);
  }
  void HeightHelper(AVLNode<KeyType, ValueType>*& set){
      AVLNode<KeyType, ValueType> *right = set->getRight(), *left = set->getLeft();
      if(right == NULL && left == NULL){ 
        set -> setHeight(0);
        return;
      } else if(right == NULL || left == NULL ) {
        if(right == NULL) set->setHeight(left->getHeight()+1);
        else set->setHeight(right->getHeight()+1);
      } else {
        int right_height = right -> getHeight(), left_height = left->getHeight();
        if(right != NULL  && left != NULL) set->setHeight( std::max(right_height, left_height) + 1 );
        if(abs(right_height - left_height) > 1) balance(set);
      }
  }
  void HeightSetter(AVLNode<KeyType, ValueType>* node){
    if(node == NULL) return;
    HeightHelper(node);
    HeightSetter(node->getParent());
  }
  void balance(AVLNode<KeyType, ValueType>* z){
    AVLNode<KeyType, ValueType> *left = z -> getLeft(), *right = z->getRight(), *parent = z->getParent();
    if(left == NULL)
      if(right == NULL || (right -> getLeft() == NULL &&right -> getRight() == NULL) ) HeightHelper(z);
    if(right == NULL)
      if(left == NULL || (left -> getLeft() == NULL && left -> getRight() == NULL) ) HeightHelper(z);
    AVLNode<KeyType, ValueType> *y = left -> getHeight() > right -> getHeight() ? left : right;
    AVLNode<KeyType, ValueType> *x = y -> getLeft() -> getHeight() > y -> getRight() -> getHeight() ? left : right;
    if(z -> getLeft() == y && x == y -> getLeft() ){
      Left(z, y, parent);
      HeightHelper(y);
    }
    else if( z-> getRight() == y && x == y->getRight() ){
      Right(z,y,parent);
      HeightHelper(y);
    }
    else if( z-> getRight() == y && x == y -> getLeft() ){
      Right(y,x,z);
      Left(z,y,parent);
      HeightHelper(x);
    } else{
      Left(y,x,z);
      Right(z,y,parent);
      HeightHelper(x);
    }
  }
  void Left(AVLNode<KeyType, ValueType>*& z,AVLNode<KeyType, ValueType>*& y, AVLNode<KeyType, ValueType>*& parent ){
    parent->getLeft() == z ? parent ->setLeft(y): parent -> setRight(y);
    y ->setParent(z->getParent());
    z->setLeft(y->getRight());
    y->setRight(z);
    z = y;
  }
  void Right(AVLNode<KeyType, ValueType>*& z, AVLNode<KeyType, ValueType>*& y, AVLNode<KeyType, ValueType>*& parent){
    parent->getLeft() == z ? parent ->setLeft(y): parent -> setRight(y);
    y ->setParent(z->getParent());
    z->setRight(y->getLeft());
    y->setLeft(z);
    z = y;
  }
};
#endif
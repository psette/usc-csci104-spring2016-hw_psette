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
  void insert (const std::pair<const KeyType, ValueType>& new_item){
    insertHelper(static_cast<AVLNode<KeyType,ValueType>*>(this->root),new_item,static_cast<AVLNode<KeyType,ValueType>*>(this->root));
  }
  void remove (const KeyType &toRemove){
    try{
      removeHelper(this->root,toRemove);
    }catch (std::logic_error& e){
      std::cerr<<"ERROR"<<std::endl;
    }
  }
private:
  AVLNode<KeyType, ValueType>* insertHelper(AVLNode<KeyType, ValueType>* node, const std::pair<const KeyType, ValueType>& new_item, AVLNode<KeyType, ValueType>* parent){
    if(node == NULL){
      bool need_to_insert = (parent->getRight() == NULL && parent->getLeft() == NULL);
      AVLNode<KeyType, ValueType>* inserting = new AVLNode<KeyType, ValueType>(new_item.first,new_item.second, parent);
      inserting -> setRight(NULL);
      inserting -> setLeft(NULL);
      if(need_to_insert)  HeightSetter(parent);
      return inserting;
    }
    if(new_item.first > node->getKey()) node -> setRight(insertHelper(node->getRight(), new_item, node));
    if(new_item.first < node->getKey()) node -> setLeft(insertHelper(node->getLeft(), new_item, node));
    return node;
  }
  bool hasSibiling(AVLNode<KeyType, ValueType>* node){
    AVLNode<KeyType, ValueType>* parent = node ->getParent();
    return parent-> getLeft() == node ? parent -> getRight() : parent -> getLeft() != NULL;
  }
  void SetBalanceAndHeights(AVLNode<KeyType, ValueType>* node ){
    if( !hasSibiling() ){
    AVLNode<KeyType, ValueType>* temp = node;
      while(node != this->root){
        node ->setHeight(node->getHeight() - 1);
        node = node -> getParent();
        if( node->getLeft() == NULL || node->getRight() == NULL) continue;
        if( abs(node ->getLeft() -> getHeight() - node ->getLeft()->getHeight()) > 1 ) balance(node);
      }
    }
  }
  void removeHelper(AVLNode<KeyType, ValueType>* node, const KeyType& value) {
    if(node == NULL) throw std::logic_error("Not in Tree");
    else if(node -> val == value) {
      AVLNode<KeyType, ValueType>* parent = node -> getParent();
      if ((node->getLeft() == NULL) && (node->getRight() == NULL)){
        parent -> getLeft() == node ? parent -> setLeft(NULL) : parent ->setRight(NULL);
        SetBalanceAndHeights(node);
      } else if( node -> getRight() == NULL){
          parent -> getLeft() == node ? parent -> setLeft(node->getLeft()) : parent ->setRight(node -> getRight());
          SetBalanceAndHeights(node);
      } else {
        AVLNode<KeyType, ValueType>* temp = node -> getRight();
        while( temp -> getLeft() != NULL) temp = temp -> getLeft();
        parent -> getLeft() == node ? parent -> setLeft(temp) : parent ->setRight(temp);
        temp ->setParent(parent);
        temp -> setLeft(node->getLeft());
        temp -> setRight(node->getRight());
        SetBalanceAndHeights(temp);
      }
      delete node;
    } else removeHelper(node -> first > value ? node -> getLeft() : node -> getRight(), value);
  }
  void HeightHelper(AVLNode<KeyType, ValueType>*& set){
      AVLNode<KeyType, ValueType> *right = set->getRight(), *left = set->getLeft();
      if(right == NULL && left == NULL){ 
        set -> setHeight(0);
        return;
      } else if(right == NULL || left == NULL ) {
        if(right == NULL) set->setHeight(left->getHeight()+1);
        else set->setHeight(right->getHeight()+1);
        return;
      } else {
        int right_height = right -> getHeight(), left_height = left->getHeight();
        if(right != NULL  && left != NULL) set->setHeight( std::max(right_height, left_height) + 1 );
        if(abs(right_height - left_height) > 1) balance(set);
      }
  }
  void HeightSetter(AVLNode<KeyType, ValueType>* node){
    if(node->getParent()  == NULL) return;
    HeightHelper(node);
    HeightSetter(node->getParent());
  }
  void balance(AVLNode<KeyType, ValueType>* z){
    AVLNode<KeyType, ValueType> *left = z -> getLeft(), *right = z->getRight(), *parent = z->getParent();
    AVLNode<KeyType, ValueType> *y = left -> getHeight() > right -> getHeight() ? left : right;
    AVLNode<KeyType, ValueType> *x = y -> getLeft() -> getHeight() > y -> getRight() -> getHeight() ? left : right;
    if(z -> getLeft() == y && x == y -> getLeft() ) {
      Left(z, y, parent);
      HeightHelper(y);
    }
    else if( z-> getRight() == y && x == y->getRight() ) {
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
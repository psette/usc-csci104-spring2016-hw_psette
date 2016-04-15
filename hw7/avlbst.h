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
    insertHelper(static_cast<AVLNode<KeyType,ValueType>*>(this->root),new_item, NULL);
  }
  void remove (const KeyType &toRemove){
   try{
      removeHelper(static_cast<AVLNode<KeyType,ValueType>*>(this->root),toRemove);
    }catch (std::logic_error& e){
      std::cerr<<"ERROR"<<std::endl;
    }
  }
private:
  bool insertHelper(AVLNode<KeyType, ValueType>* node, const std::pair<const KeyType, ValueType>& new_item,AVLNode<KeyType, ValueType>* parent){
    if(node == NULL){
      node = new AVLNode<KeyType, ValueType>(new_item.first,new_item.second,parent);
      if(parent == NULL){
        this->root = node;
      } else if( new_item.first > parent->getKey()) parent->setRight(node);
      else parent->setLeft(node);
    } else if(new_item.first < node->getKey()){
     if(insertHelper(node->getLeft(), new_item,node)){
       AVLNode<KeyType, ValueType> *right = node -> getRight(), *left = node-> getLeft();
       int right_height = HeightHelper(right), left_height = HeightHelper(left);
       if(abs(left_height - right_height) > 1){
        if(new_item.first > node -> getLeft() -> getKey())  RightShift(node);
        else {
            LeftShift(right); RightShift(node);
        }
        return true;
      } else return false;
     }
    } else{
      if(insertHelper(node->getRight(), new_item,node)){
        AVLNode<KeyType, ValueType> *right = node -> getRight(), *left = node-> getLeft();
        int right_height = HeightHelper(right), left_height = HeightHelper(left);
        if(abs(left_height - right_height) > 1){
          if(new_item.first < node -> getRight() -> getKey())   LeftShift(node);
          }else {
            RightShift(left); LeftShift(node);
        }
        return true;
      } else return false;
    } 
    return false; 
  }
  bool hasSibiling(AVLNode<KeyType, ValueType>* node){
    AVLNode<KeyType, ValueType>* parent = node ->getParent();
    return parent-> getLeft() == node ? parent -> getRight() != NULL : parent -> getLeft() != NULL;
  }
  void SetBalanceAndHeights(AVLNode<KeyType, ValueType>* node){
    if(node -> getParent() == NULL ) return;
    if(node -> getParent() ->getLeft() == NULL && node->getParent()->getRight() ){
      while(node -> getParent() != NULL){
        HeightHelper(node);
        node = node -> getParent();
      }
    }
  }
  /*
  Remove helper removes the requested node, recursivley. If it is not in the tree, it throws an error.
  I couldn't get the root removal properly implemented but for the rest it works
  If there are no children
  */
  void RightShift(AVLNode<KeyType, ValueType>*& node){
    AVLNode<KeyType, ValueType>* left = node -> getLeft(), *parent = node ->getParent();
    node -> setLeft(left -> getRight());
    if(node->getLeft() != NULL) node -> getLeft() -> setParent(node);
    left->setRight(node);
    if(left->getRight() != NULL) node->getRight()->setParent(left);
    node = left;
    node->setParent(parent);
  }
  void LeftShift(AVLNode<KeyType, ValueType>*& node){
    AVLNode<KeyType, ValueType> *right = node->getRight(), *parent = node->getParent();
    node->setRight(right->getLeft());
    if ( node->getRight()) node->getRight()->setParent(node);
    right->setLeft(node);
    if ( right->getLeft() ) right->getLeft()->setParent(right);
    node = right;
    node->setParent(parent);
  }
  void removeHelper(AVLNode<KeyType, ValueType>* node, const KeyType& value){
    if(node == NULL) throw std::logic_error("Not in Tree");
    else if(node -> getKey() == value) {
      AVLNode<KeyType, ValueType>* parent = node -> getParent();
      if(parent == NULL){

        if(node -> getLeft() == NULL && node-> getRight() == NULL) {
          delete node; 
          this->root = NULL;
        } else if(node->getLeft() == NULL || node ->getRight() == NULL){
          this -> root = node -> getRight() == NULL ? node -> getLeft() : node -> getRight();
          this -> root -> setParent(NULL);
          delete node;
          SetBalanceAndHeights(static_cast<AVLNode<KeyType,ValueType>*>(this->root),true);
        } else {
          AVLNode<KeyType, ValueType>* switch_to = node -> getLeft(), *temp = NULL;
          while( switch_to -> getRight() != NULL) switch_to = switch_to -> getRight();
          temp = switch_to -> getParent();
          temp -> setRight(NULL);
          switch_to ->setParent(NULL);
          switch_to -> setLeft(node->getLeft());
          switch_to -> setRight(node->getRight());
          node -> getLeft() -> setParent(switch_to);
          node -> getRight() -> setParent(switch_to);
          this->root = switch_to;
          delete node;
          SetBalanceAndHeights(temp,true);
        }

      } else if ((node->getLeft() == NULL) && (node->getRight() == NULL)){
        parent -> getLeft() == node ? parent -> setLeft(NULL) : parent ->setRight(NULL);
        delete node;
        SetBalanceAndHeights(parent);
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
  int HeightHelper(AVLNode<KeyType, ValueType>*& set){
      if(set == NULL) return 0;
      AVLNode<KeyType, ValueType> *left_node = set->getLeft(), *right_node = set->getRight();
      int left = HeightHelper(left_node), right = HeightHelper(right_node);
      return std::min(left,right) + 1;
  }
  void HeightSetter(AVLNode<KeyType, ValueType>* node){
    node -> setHeight(HeightHelper(node));
  }
};
#endif
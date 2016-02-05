#include "llistint.h"
#include <cstdlib>
#include <stdexcept>
LListInt::LListInt(){
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}
LListInt::~LListInt(){
  clear();
}
bool LListInt::empty() const{
  return size_ == 0;
}
int LListInt::size() const{
  return size_;
}
/**
 * Complete the following function
 */
void LListInt::insert(int loc, const int& val){
  if(loc < 0 || loc > size_ ) return; //If the out of bounds, return
  if(loc == 0 && size_ == 0) {        //If loc and size = 0, initialize the head and tail
    head_ = new Item;
    tail_ = head_;
  }
  Item *new_node = new Item;          //Create new node to insert
  if(loc == 0){                       //If inserting at the begining
    new_node -> prev = NULL;          //Set the previous pointer as NULL
    new_node -> next = head_;         //Set new node's next ptr to head
    head_ -> prev = new_node;         //Set the head's prev ptr to the new node
    head_ = new_node;                 //Set head as the new node
  }
  else if(loc == size_){              //If inserting at end
    new_node -> prev = tail_;         //Set the new node's previous pointer to tail
    tail_ -> next = new_node;         //Set tail's next ptr to the new node
    new_node -> next = NULL;          //Set the new node's next ptr to NULL
    tail_ = new_node;                 //Set tail as new node
  }
  else{
    Item *temp = getNodeAt(loc);          //Get the node at given location 
    new_node -> prev = temp -> prev;      //Set the new's prev as the old's prev
    new_node -> prev -> next = new_node;  //Set new's prev's next as new
    new_node -> next = temp;              //Set new's next as old
    temp -> prev = new_node;              //Set old's prev as new
  }
  set(loc,val);                      //Set value at given location
  size_++;                           //Increment size by 1
  return;
}
/**
 * Complete the following function
 */
void LListInt::remove(int loc){
  Item *temp = getNodeAt(loc);            //Get the node at a given location
  if(temp == NULL || size_ == 0) return;  //If invalid loc or nothing to remove, return
  if(loc == size_){                       //If removing last element
    tail_ = tail_ -> prev;                //Set tail as the previous node
    tail_ -> next = NULL;                 //Set tail's next ptr as NULL
  }
  if(loc == 0){                           //If removing from the initial element
    head_ = head_ -> next;                //Set head as the item after head
    head_ -> prev = NULL;                 //Set head's prev as NULL
  }
  else{
    temp -> next -> prev = temp -> prev;  //Set rmv's node's next's prev as rmv's prev
    temp -> prev -> next = temp -> next;  //Set rmv's prev's next as remv's next
  }
  delete temp;                            //Delete
  size_--;                                //Decrease size
  return;
}
void LListInt::set(int loc, const int& val){
  Item *temp = getNodeAt(loc);
  temp->val = val;
  return;
}
int& LListInt::get(int loc){
  if(loc < 0 || loc >= size_){
    throw std::invalid_argument("bad location");
  }
  Item *temp = getNodeAt(loc);
  return temp->val;
}

int const & LListInt::get(int loc) const{
  if(loc < 0 || loc >= size_) throw std::invalid_argument("bad location");
  Item *temp = getNodeAt(loc);
  return temp->val;
}

void LListInt::clear(){
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
/**
 * Complete the following function
 */
LListInt::Item* LListInt::getNodeAt(int loc) const{
  if(loc < 0 || loc > size_ ) return NULL;  //If location invalid, return NULL
  Item *temp = head_;                                   //Set temp as head
  for(int i = 0; i < loc; i++) temp = temp -> next;     //Advance loc times
  return temp;                                          //Return node
}
#include "../lib/llistint.h"
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
LListInt::LListInt(const LListInt& other){
  duplicate(other);
}

LListInt& LListInt::operator=(const LListInt& other){
  if(this != &other) {
    this -> clear();
    duplicate(other);
  }
  return *this;
}
LListInt LListInt::operator+(const LListInt& other) const{
  LListInt temp = LListInt(*this);
  for(int i = 0; i < other.size_; i++)  temp.insert(i + this -> size(), other.get(i));
  return temp;
}

int const & LListInt::operator[](int position) const{
  return get(position);
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
  Item * new_node = new Item;
  if(loc < 0 || loc > size_) return;
  else if (size_ == 0){
    head_ = new_node;
    tail_ = new_node;
    new_node -> next = NULL;
    new_node -> prev = NULL;
  }
  else if (loc == 0){
    new_node -> prev = NULL;
    new_node -> next = head_;
    head_ -> prev = new_node;
    head_ = head_ -> prev;
  }
  else if(loc == size_){
    new_node -> prev = tail_;
    new_node -> next = NULL;
    tail_ -> next = new_node;
    tail_ = new_node;
  }
  else{
    Item *Old = getNodeAt(loc);
    new_node -> prev = Old -> prev;
    new_node -> prev -> next = new_node;
    new_node -> next = Old;
    Old -> next = new_node;
  }
  new_node -> val = val;
  size_++;
  return;
}
void LListInt::remove(int loc){
  if(loc > size_ || loc < 0) return;
  Item* temp = getNodeAt(loc);
  if(size_ == 1){
    head_ = NULL;
    tail_ = NULL;
  }
  else if(loc == 0){                           //If removing from the initial element
    head_ = head_ -> next;                //Set head as the item after head
    head_ -> prev = NULL;                 //Set head's prev as NULL
  }
  else if(loc == size_){                       //If removing last element
    tail_ = tail_ -> prev;                //Set tail as the previous node
    tail_ -> next = NULL;                 //Set tail's next ptr as NULL
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
void LListInt::duplicate(const LListInt& other){
  this -> size_ = other.size_;
  if(other.head_ != NULL){
    head_ = new Item;
    head_ -> val = other.head_ -> val;
    head_ -> prev = NULL;
    Item *it_from = other.head_;
    Item *it_to = this -> head_;
    while(it_from -> next){
      it_to -> next = new Item;
      it_to -> next -> val = it_from -> next -> val;
      it_to -> next -> prev = it_to;
      it_from = it_from -> next;
      it_to = it_to -> next;
    }
    this -> tail_ = it_to;
    this -> tail_ -> next = NULL;
  }
}

LListInt::Item* LListInt::getNodeAt(int loc) const{
  if(loc < 0 || loc > size_ ) return NULL;  //If location invalid, return NULL
  Item *temp = head_;                                   //Set temp as head
  for(int i = 0; i < loc; i++) temp = temp -> next;     //Advance loc times
  return temp;                                          //Return node
}

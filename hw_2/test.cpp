#include "llistint.h"
#include <iostream>

using namespace std;

int main() {
  LListInt * list = new LListInt();
  // Check if the list is initially empty.
  if (list->empty()) cout << "SUCCESS: List is empty initially." << endl;
  else cout << "FAIL: List is not empty initially when it should be." << endl;
  // Insert an item at the head.
  list->insert(0, 3);
  // Check if the list is still empty.
  if (!list->empty()) cout << "SUCCESS: List is not empty after one insertion." << endl;
  else cout << "FAIL: List is empty after one insertion." << endl;
  if (list->size() == 1) cout << "SUCCESS: List has size 1 after one insertion." << endl;
  else cout << "FAIL: List size " << list->size() << " after insertion." << endl;
  // Check if the value is correct.
  if (list->get(0) == 3) cout << "SUCCESS: 3 is at the 0th index of the list." << endl; 
  else cout << "FAIL: " << list->get(0) << " is at the 0th index of the list." << endl;
  //Insert out of bounds
  list->insert(90,3);
  if (list->size() == 1) cout << "SUCCESS: List has size 1 after no insertions." << endl;
  else cout << "FAIL: List size " << list->size() << " after insertion." << endl;
  //Insert out of bounds
  list->insert(-1,3);
  if (list->size() == 1) cout << "SUCCESS: List has size 1 after no insertions." << endl;
  else cout << "FAIL: List size " << list->size() << " after insertion." << endl;
  //Insert at begining 
  list->insert(0,90);
  if (list->size() == 2) cout << "SUCCESS: List has size 2 after insertion." << endl;
  else cout << "FAIL: List size " << list->size() << " after insertion." << endl;
  // Check if the value is correct.
  if (list->get(0) == 90) cout << "SUCCESS: 90 is at the 0th index of the list." << endl; 
  else cout << "FAIL: " << list->get(0) << " is at the 0th index of the list." << endl;
  // Check if the value is correct.
  if (list->get(1) == 3) cout << "SUCCESS: 3 is at the 1th index of the list." << endl; 
  else cout << "FAIL: " << list->get(0) << " is at the 1th index of the list." << endl;
  // Insert at end of List
  list->insert(list->size(),80);
  if (list->size() == 3) cout << "SUCCESS: List has size 3 after insertion." << endl;
  else cout << "FAIL: List size " << list->size() << " after insertion." << endl;
  //Insert at middle
  list->insert(1,12);
  //Check elements
  if(list->get(0) == 90 && list->get(1) == 12 && list->get(2) == 3 && list->get(3) == 80)
    cout<< "SUCCESS: LIST ELEMNTS ARE CORRECT " << endl;
  else cout<< "FAIL" <<endl;
  //Remove invalid bounds
  list->remove(-1);
  list->remove(90);
  //Check if elements are correct
  if(list->get(0) == 90 && list->get(1) == 12 && list->get(2) == 3 && list->get(3) == 80)
    cout<< "SUCCESS: LIST ELEMNTS ARE CORRECT " << endl;
  else cout<< "FAIL" <<endl;
  //Remove the first element
  list->remove(0);
  //Check if elemnts are correct
  if(list->get(0) == 12 && list->get(1) == 3 && list->get(2) == 80)
    cout<< "SUCCESS: LIST ELEMNTS ARE CORRECT " << endl;
  else cout<< "FAIL" <<endl;
  //Remove middle element
  list->remove(2);
  if(list->get(0) == 12 && list->get(1) == 3)  cout<< "SUCCESS: LIST ELEMNTS ARE CORRECT " << endl;
  else cout<< "FAIL" <<endl;
  //Remove last element
  list->remove(1);
  if(list->get(0) == 12)  cout<< "SUCCESS: LIST ELEMNTS ARE CORRECT " << endl;
  else cout<< "FAIL" <<endl;
  //Remove only element left, check if empty
  list->remove(0);
  list->clear();
  if (list->empty()) cout << "SUCCESS: List is empty" << endl;
  else cout << "FAIL: List is not empty initially when it should be." << endl;
  // Clean up memory. 
  delete list;
}


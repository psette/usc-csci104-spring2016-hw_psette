#include <vector>
#include <utility>
#include <exception>
#include <stdexcept>
template <typename T> 
class MinHeap {
     public:
       MinHeap (int d);
      ~MinHeap ();
       void add (T item, int priority);
       const T & peek () const;
       void remove ();
       bool isEmpty ();
       void trickle_up(int);
       void trickle_down(int);
       void swap(std::pair <int,T>&, std::pair <int,T>&);
   private:
            int dvalue;
      std::vector<std::pair<int,T> > tree_vec;
};
template <typename T> 
MinHeap<T>::MinHeap(int d):dvalue(d){};
template <typename T> 
MinHeap<T>::~MinHeap() {};
template <typename T> 
void MinHeap<T>::add (T item, int priority){
  tree_vec.push_back(std::make_pair(priority, item));
  trickle_up( tree_vec.size() - 1 );
};
template <typename T> 
const T & MinHeap<T>::peek () const{
   if( tree_vec.empty() )  throw std::logic_error("peek empty array");
   return tree_vec[0].second;
 };
template <typename T> 
void MinHeap<T>::remove (){  
   if( isEmpty() )  throw std::logic_error("remove empty array");
   tree_vec.erase(tree_vec.begin());
   trickle_down(0);
};
template <typename T> 
bool MinHeap<T>::isEmpty (){
   return tree_vec.empty();
};
template <typename T> 
void MinHeap<T>::swap(std::pair <int,T>& A, std::pair <int,T>& B){
   std::pair <int,T> temp = A;
   A = B;
   B = temp;
};
template <typename T> 
void MinHeap<T>::trickle_up(int child){
   int parent = (child - 1) / dvalue;
   if(child > 0 && tree_vec[child].first < tree_vec[parent].first ){
      swap(tree_vec[child], tree_vec[parent]);
      trickle_up(parent);
   }
};
template <typename T> 
void MinHeap<T>::trickle_down(int parent){
   int child = dvalue * parent + 1, min = tree_vec[parent].first, min_loc = 0;
   for(int i = 0; i < dvalue; ++i, ++child){
      if(child < tree_vec.size() && min > tree_vec[child].first){
         min = tree_vec[child].first;
         min_loc = child;
      }
   }
   if(min_loc != 0){
     swap(tree_vec[min_loc], tree_vec[parent]);
     trickle_down(min_loc);
   }
};
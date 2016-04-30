## HW 8 - CS 104 Student Repository

- **Name**: Pietro Sette
- **USC ID**: 8626509080
- **Email**: psette@usc.edu

- **Splay Tree**
  - http://imgur.com/soneJxJ

- **Hash Table**
  - heap.h

- **Comparisons**
  - Type in "qmake && make && ./debugger" to compile and run
What large input cases did you use?

I used Pride and Prejudice, The Bible and German Science Reader

Which implementation ran faster? How much faster was it? 

HashTable was about twice as fast for Pride and Bible

Why do you think that one was faster? Was it because of the chosen input or is there a guarantee made that affects this?

Hash table was faster because Splay has amortized O(log n) insert whereas hash has amortized O(1) insert. This is so because Splay needs to search for the value whereas hash just checks the index of the array.

How do you think the running time would compare to the two if you were to implement your Map in the following fashions? Briefly justify each, although you do not need to quantify how much slower/faster with any specificity.
Unsorted List
Sorted list
Binary search tree, non-rotating variety
Binary search tree with AVL balancing

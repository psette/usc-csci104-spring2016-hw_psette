## HW 8 - CS 104 Student Repository

- **Name**: Pietro Sette
- **USC ID**: 8626509080
- **Email**: psette@usc.edu

- **Splay Tree**
  - splaytree.h

- **Hash Table**
  - hashtable.h

- **Comparisons**
What large input cases did you use?

I used Pride and Prejudice, The Bible, Hamlet, and German Science Reader

Which implementation ran faster? How much faster was it? 

HashTable was about twice as fast for Pride and Bible

Why do you think that one was faster? Was it because of the chosen input or is there a guarantee made that affects this?

Hash table was faster because Splay has amortized O(log n) insert whereas hash has amortized O(1) insert. This is so because Splay needs to search for the value whereas hash just checks the index of the array.

How do you think the running time would compare to the two if you were to implement your Map in the following fashions? Briefly justify each, although you do not need to quantify how much slower/faster with any specificity.

Unsorted List Would be slower find O(n) but O(1) insertion

Sorted list   Would be slower insert O(n) but O(log(n)) find

Binary search tree, non-rotating variety find would be O(n) and insert would be O(log(n))

Binary search tree with AVL balancing find and insert would be O(log(n))

# CS 104 Student Repository

- **Name**: Pietro Sette
- **USC ID**: 8626509080
- **Email**: psette@usc.edu
- **PROBLEM 2**
Done, in full, in the hw3.txt file

- **PROBLEM 3**
contains source code for Copy Constructors and Operator Overloading. The tests can be compiled and ran by typing in make llisttest.


- **PROBLEM 4**
stackint.cpp contains functions for stack (empty, push, top, and pop)

- **PROBLEM 5** 
sape.cpp contains the code for the simple arithmetic parser. Not function will return 0 if passed in >>>>>> or something similar. Otherwise, will evaluate expressions in file passed in via command line. If the formula is improperly formatted, it will print Malformed.

- **MAKEFILE** 
Makefile is included and on make, it runs the google test cases for problem 3 and 4. It also runs sape with input file in.txt
make sape makes problem 5 and creates executable sape in the bin directory
make llisttest makes problem 3 and creates executable llisttest in the bin directory
make stackint makes problem 4 and creates executable stackint in the bin directory

- **listtest.cpp** 
A handful of google test cases for each individual functions (copy constructor, operator=, operator+, and []).

- **stacktest.cpp** 
A handful of google test cases for each individual functions (empty, push, top, and pop).

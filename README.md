ABOUT
* This program takes in an augmented matrix from a text file and converts
  it to echelon and reduced echelon form using Gaussian Elimination.

TESTING
* To run your own test cases, create a .txt file with the 
  following format: (samples under test cases/)

matrix.txt
--------------------
Number of rows
Number of columns
Entries of row 1
Entries of row 2
...
Entries of row n
--------------------

EXECUTION
* To run code, enter into the terminal:
g++ matrix.cpp -o matrix
./matrix "filename.txt"
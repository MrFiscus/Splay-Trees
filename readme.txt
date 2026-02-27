Assignment 1 Part 2 – Splay Trees
Spring 2026

The code implements a Splay Tree which has the following features:-
1.Implements Delete Node() and Search Node() functions for both the bottom-up and top down approached.
-DeleteNode() -> delete the key and spay its parent in one pass.
-SearchNode() -> search and splay the key in one pass

2. Implemented a top down semi splay function to reduce the operation which does the following:-
-Instead of a fully splaying to the root, splays the node half-way up the tree
-Uses a rotation limit parameter, then stop splaying after k rotations (option 1)

3. Implemented a top-down weighted-splay function which has a cache-like
behavior and does the following:-
- Stores access frequency of each node and increments the weight after ever
successful search.
-Before the rotation, checks the weight and rotates only if child weight >= parent weight (option 1)

4. Benchmarks search() on the above variations of the splay trees using the four different access patterns and measures the following matrices:
- Total rotation count
- Average search depth
- Total time

5. Uses the provided exception handling to manage invalid operations and edge
cases

6.Uses the make files to automate compiling and running of the program


Access Patterns Used:
1. sequential.txt
2. uniform_random.txt
3. working_set.txt
4. zipf_skewed.txt

Files:
accessPattern/
sequential.txt
uniform_random.txt
working_set.txt
zipf_skewed.txt

Bottomup/
customErrorClass.cpp
customErrorClass.h
mainsplay.cpp
Makefile
splay.cpp
splay.h

Screenshot/
Bottomup.png
Task2.png
Task3.png
Topdown.png

Task2/
customErrorClass.cpp
customErrorClass.h
mainsplay.cpp
Makefile
splay.cpp
splay.h

Task3/
customErrorClass.cpp
customErrorClass.h
mainsplay.cpp
Makefile
splay.cpp
splay.h

Topdown/
customErrorClass.cpp
customErrorClass.h
mainsplay.cpp
Makefile
splay.cpp
splay.h

A2_p2.pdf
readme.txt
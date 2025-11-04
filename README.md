# **Vector Calculator** 
###  This program (attempts to) replicate similar functionality of a Vector arithmetic in MATLAB. It is not able to do everything, but simple arithmetic such as addition, subtraction and multiplication (dot and cross products) are possible. 
#

#### --**BUILD PROGRAM WITH** "make" (make file included)
#### --**RUN PROGRAM WITH**   "./vect" (can change executable name within Makefile)
#
 ***User Commands***
 * help: Prints out all commands
 * list: Prints out all valid Vectors in list
 * clear: Clears list of Vectors
 * quit: Ends program
 * read / write: Allows the user to read / write to / from a .csv or .txt file
 

***Memory allocation*** 

The default number of vectors is initialized to 3 for the a simple assignment operation such as a + b = c, but as soon as a 4th vector is recognized in the list, 3 more spots are made through dynamic memory allocation (realloc() function). The list of vectors should continue to allocate 3 more spaces for as many vectors are needed, but is limited up to 52 since any given vector can only be assigned to a single letter, upper and lower case.

 


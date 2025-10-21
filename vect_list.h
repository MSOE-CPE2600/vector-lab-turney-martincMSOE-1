/******************************************************************************
 * File vect_list.h
 * Description : .h file to declare vect list functions
 * Author: Chris Martin
 * Date: 10/21/25
 * Compile with make 
 *****************************************************************************/

Vector find(char *name);
 
void list();
 
void clear();

Vector create(char name[20], float x, float y, float z);

void insert(Vector new);




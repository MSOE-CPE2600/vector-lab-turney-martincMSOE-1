/******************************************************************************
 * File vect_list.h
 * Description: .h file to declare vect list functions
 * Author: Chris Martin
 * Date: 11/4/25
 * Compile with make 
 *****************************************************************************/

void initialize_list();

void load();

void save(Vector v, char *fname);

void save_all(char *fname);

Vector find(char *name);
 
void list();
 
void clear();

Vector create(char name[20], float x, float y, float z);

void insert(Vector new);

void free_list();




/******************************************************************************
 * File vect_list.c
 * Description : functions to manage a list of vectors (listing, clearing, etc)
 * Author: Chris Martin
 * Date: 10/21/25
 * Compile with make 
 *****************************************************************************/

#include <stdio.h>
#include <string.h>
#include "vector.h"
//#include "vect_list.h"
#define SIZE 10

// list, clear, insert (add vect to list), 

Vector vect_list[SIZE];


/* 
 * Verifies the existance of a given Vector based on the name
 * If found: return vector name and details
 * If Not found: return Null name and 0.0 for each plane
 */
Vector find(char *name) {
    for (int i = 0; i < SIZE; i++) {
        if (strcmp(vect_list[i].name, name) == 0) {
            return vect_list[i]; // return if vector found
        }
    }

    Vector dne = {"NULL", 0.0, 0.0, 0.0}; // vecor does not exist
    return dne; //DONT add to list, just return
}

/* Lists all of the current Vectors in the list*/
void list() {
    for (int i = 0; i < SIZE; i++){
        if (strcmp(vect_list[i].name, "NULL") != 0){
            printf("%s {%.3f, %.3f. %.3f} \n", vect_list[i].name, vect_list[i].x, vect_list[i].y, vect_list[i].z);
        }
    }
    printf("\n");
}

/* Clears current list of Vectors*/
void clear () {
    for (int i = 0; i < SIZE; i++) {
        vect_list[i] = (Vector) {"NULL", 0.0, 0.0, 0.0};
    }
}

/* Creates a new vector */ //(may not need to retunn vector)
Vector create(char name[20], float x, float y, float z) {
    // may need to verify that list does not contain vector with same name
    Vector v;
    strcpy(v.name, name);
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

void insert(Vector new) {
    int found = 0;
     for (int i = 0; i < SIZE; i++){ // if same vect exists in array already
         if(!strcmp(vect_list[i].name, new.name)){
            found = 1;
            printf("OVERWRITING VECTOR %s \n", new.name);
            memcpy(&vect_list[i], &new, sizeof(Vector));
            return;
         }
     }

    // if new vect is not in list
    if(found == 0){ 
        for (int i = 0; i < SIZE; i++){ // looking for empty spot in list 
          if (strcmp(vect_list[i].name, "NULL") == 0){ 
            memcpy(&vect_list[i], &new, sizeof(Vector));
            break;
          }
        }
    }
}



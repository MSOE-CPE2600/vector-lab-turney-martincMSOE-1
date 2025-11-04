/******************************************************************************
 * File vect_list.c
 * Description : functions to manage a list of vectors (listing, clearing, etc)
 * Author: Chris Martin
 * Date: 11/4/25
 * Compile with make 
 *****************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "vector.h"
#include "vect_list.h"
#define INIT_CAPACITY 2

// list, clear, insert (add vect to list)

//Vector vect_list[SIZE];
static Vector *vect_list;
static int current_capacity = INIT_CAPACITY;
static int size = 0;

void load(char *fname) {

    FILE *fp = fopen(fname, "r");
    if (!fp) {
        printf("ERROR: Wrong file name or Could not open file %s :( \n", fname);
        return;
    }

    if (vect_list == NULL) { // if initially empty or cleared recently
        initialize_list();
    }

    /* 
     * Continuously read contents of file
     * Check if character is index is character / digt
     * write vector data to available memory location
     */
    char line[50]; // could reduce to 4 since only have maximum of 4 characters?
    Vector v;
    //float x, y, z;

    while (fgets(line, 50, fp)){
        if (isalpha(line[0])) { // Verify 1st character is letter (vector name)
            sscanf(line, "%s %f %f %f", v.name, &v.x, &v.y, &v.z);
            insert(v);
        }
    }
    fclose(fp);
}

void save(Vector v, char *fname) {
    FILE *fp = fopen(fname, "a");
    if (!fp) {
        printf("ERROR: Could not open file properly :(.. %s\n", fname);
        return;
    }

    fprintf(fp, "%s ,%.3f ,%.3f ,%.3f\n", v.name, v.x, v.y, v.z);
    fclose(fp);
}

void save_all(char *fname) {
    FILE *fp = fopen(fname, "w");
    if (!fp || !strcasestr(fname,".csv")) {
        printf("ERROR: Unsupported file/ Could not properly :( %s\n", fname);
        return;
    }

    for (int i = 0; i < size; i++) {
        fprintf(fp, "%s ,%.3f ,%.3f ,%.3f\n", (vect_list + i)->name, (vect_list + i)->x, (vect_list + i)->y, (vect_list + i)->z);
    }
    fclose(fp);
}
 
/* Initialize vector list (Cant Initialize Struct pointer outside of a method?) */
void initialize_list() {
    vect_list = malloc(INIT_CAPACITY * sizeof(Vector)); // may need to check for erroe allocating mem?    
    current_capacity = INIT_CAPACITY;
    size = 0;
}

/* 
 * Verifies the existance of a given Vector based on the name
 * If found: return vector name and details
 * If Not found: return Null name and 0.0 for each plane
 */
Vector find(char *name) {
    for (int i = 0; i < size; i++) {
        if (strcmp((vect_list+i)-> name, name) == 0) {
            return *(vect_list+i); // return if vector found
        }
    }

    Vector dne = {"NULL", 0.0, 0.0, 0.0}; // vecor does not exist
    return dne; //DONT add to list, just return
}

/* Lists all of the current Vectors in the list*/
void list() {
    for (int i = 0; i < size; i++){
        printf("%s {%.3f, %.3f, %.3f} \n", (vect_list+i)->name, (vect_list+i)->x, (vect_list+i)->y, (vect_list+i)->z);
    }
    printf("\n");
}

/* Clears current list of Vectors*/
void clear () {
    /* DYNAMIC MEM */
    // free(vect_list);
    // vect_list = malloc(INIT_CAPACITY * sizeof(Vector));
    // current_capacity = INIT_CAPACITY;
    size = 0; // feels iffy, but should work/overwrite previous vects since other functs rely on size
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
    // DYNAMIC MEMORY RESIZE IF NEEDED
    if (size >= current_capacity){
        puts("===========REALLOCATING===========");
        current_capacity *= 2;
        vect_list = realloc(vect_list, current_capacity * sizeof(Vector));
    }

    int found = 0;
    for (int i = 0; i < size; i++){ // if same vect exists in array already
        // if(!strcmp(vect_list[i].name, new.name)){
        if (!strcmp((vect_list+i) -> name, new.name)) {
           found = 1;
           printf("OVERWRITING VECTOR %s \n", new.name);
           memcpy((vect_list+i), &new, sizeof(Vector));
           return;
        }
    }

    // if new vect is not in list
    *(vect_list + size) = new;
    size++;
}

/* Free list of vectors (release memory) */
void free_list() {
    free(vect_list);
    vect_list = NULL;
    current_capacity = 0;
    size = 0;
}



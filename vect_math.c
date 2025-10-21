/******************************************************************************
 * File vect_math.c
 * Description: mathematical operations on vectors
 * Author: Chris Martin
 * Date: 10/15/25
 * Compile with make 
 *****************************************************************************/

#include <stdio.h>
#include <string.h>
#include "vector.h"
#include "vect_list.h"
 
Vector add(Vector v1, Vector v2, Vector v) { // just need 2 parameters/vectors (i think)
    v.x = v1.x + v2.x;
    v.y = v1.y + v2.y;
    v.z = v1.z + v2.z;

    if(!strcmp(v.name, "NULL")){
        printf("(%.3f, %.3f, %.3f) \n", v.x, v.y, v.z);
    } 
    printf("Sum: %s: (%.3f, %.3f, %.3f) \n", v.name, v.x, v.y, v.z);
    return v;
}

Vector sub(Vector v1, Vector v2, Vector v) {
    v.x = v1.x - v2.x;
    v.y = v1.y - v2.y;
    v.z = v1.z - v2.z;
    // add resultant vector to vect_list
    printf("Diff: %s: (%.3f, %.3f, %.3f) \n", v.name, v.x, v.y, v.z);
    return v;
}

float dot(Vector v1, Vector v2) {
    float dot;
    if (v1.z == 0 && v2.z == 0) {
        dot = (v1.x*v2.x) + (v1.y*v2.y);
        printf("Dot product: %.3f\n", dot);
        return dot;
    }
    dot = (v1.x*v2.x) + (v1.y*v2.y) + (v1.z*v2.z);
    printf("Dot product: %.3f\n", dot);
    return dot;
}

Vector cross(Vector a, Vector b, Vector v){
    // A = (1, 2, 3)
    // B = (4, 5, 6)
    // A x B = (2 * 6 - 3 * 5, 3 * 4 - 1 * 6, 1 * 5 - 2 * 4) = (-3, 6, -3)
    v.x = (a.y * b.z) - (a.z * b.y);
    v.y = (a.z * b.x) - (a.x * b.z);
    v.z = (a.x * b.y) - (a.y * b.x);
    printf("Cross product: %s: (%.3f, %.3f, %.3f) \n", v.name, v.x, v.y, v.z);
    return v;
}

Vector scalar_mult(Vector a, float scalar, Vector v){
    v.x = a.x * scalar;
    v.y = a.y * scalar;
    v.z = a.z * scalar;
    printf("Scalar product: %s: (%.3f, %.3f, %.3f) \n", v.name, v.x, v.y, v.z);
    return v;
}
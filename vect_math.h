/******************************************************************************
 * File vect_list.h
 * Description : .h file to declare Vector list functions
 * Author: Chris Martin
 * Date: 10/21/25
 * Compile with make 
 *****************************************************************************/

 Vector add (Vector v1 , Vector v2, Vector v);

 Vector sub(Vector v1, Vector v2, Vector v);

 float dot(Vector v1, Vector v2);
 
 Vector cross(Vector a, Vector b, Vector v);

 Vector scalar_mult(Vector a, float scalar, Vector v);
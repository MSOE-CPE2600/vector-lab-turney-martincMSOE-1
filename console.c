/******************************************************************************
 * File vects.h
 * Description:.h file that contains declaration the struct for vectors
 * Author: Chris Martin
 * Date: 1/4/25
 * Compile with make 
 *****************************************************************************/

 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 #include <ctype.h>
 #include "vector.h"
 #include "vect_math.h"
 #include "vect_list.h"

int main (void) {
    /* Support up to 10 Vectors*/
    // Vector vlist[10]; // may just declare the 3 needed vectors at a time

    char input[100];
    char *token1, *token2, *token3, *token4, *token5; // up to 5, minimum 3 tokens
    char operations[] = "+-*.x";
    Vector v1, v2, v3;
    //clear();
    initialize_list(); // SHOULD ONLY BE CALLED ONCE TO INITILIZE LIST OF VECTORS

    while (1) { // infinite loop to continue until quit
        // clearing tokens
        token1 = NULL;
        token2 = NULL;
        token3 = NULL;
        token4 = NULL;
        token5 = NULL;

        printf("vectcalc> ");

        /* getting stdin (console) and tokenizing inputs */
        fgets(input, 100, stdin);
        token1 = strtok(input, " \n");
        token2 = strtok(NULL, " \n");
        token3 = strtok(NULL, " \n");
        token4 = strtok(NULL, " \n");
        token5 = strtok(NULL, " \n");

        if (token1 == NULL) { // if first token empty, ERROR
            printf("ERROR: Enter something???");
            continue;
        }

        /* Single Word / Vector Commands */
        if(token2 == NULL) { // Nothing in token2 (one word)
            
            if(!strcmp(token1, "quit")||!strcmp(token1, "q")) { 
                printf("Quitting Program \n");
                free_list();  
                exit(1);

            } else if (!strcmp(token1, "help")||!strcmp(token1, "h")) {
                printf("Commands\nlist: lists all vectors\nclear: clears all vectors\nquit/q: quits program\n");

            } else if (!strcmp(token1, "list")) {
                list();

            } else if (!strcmp(token1, "clear")) {
                clear();

            } else if (strlen(token1) == 1){ // if JUST Vector name call find
                Vector search = find(token1); // verify vectors existance
                if (!strcmp(search.name , "NULL")) {
                    printf("Cannot find vector\n");
                }else{
                    printf("%s: (%.3f, %.3f, %.3f)\n", search.name, search.x, search.y, search.z);
                }
                
            } else { 
                printf("Invalid input\n");
            }

        /* I/O Operation (save / load ALL to / from particular file) */    
        } else if (token3 == NULL) { 
            char *fname = token2;
            if (!strcmp(token1, "saveall")) {
                save_all(fname);
            } else if (!strcmp(token1, "load")) {
                load(fname);
            }
        }

        /* Vector Arithmetic */
        else if (token3 != NULL) {

            /* 3 tok operations (ex. a . b) */
            if (token4 == NULL) { 

                /* I/O Operation (save ALL to particular file) */
                if (!strcmp(token1, "save")) {
                    char *fname = token3;
                    v1 = find(token2);
                    save(v1, fname);
                    continue;
                }

                v1 = find(token1);
                v2 = find(token3);

                if (!strcmp(v1.name, "NULL") || !strcmp(v2.name, "NULL")) {
                    printf("Vector(s) not found\n");
                    continue;
                }
                if (!strcmp(token2, "+")) {
                    v3 = add(v1, v2, v3);
                    continue;
                } else if (!strcmp(token2, "-")) {
                    v3 = sub(v1, v2, v3);
                } else if (!strcmp(token2, ".")) {
                    float d = dot(v1, v2);
                    continue;
                } else if (!strcmp(token2, "x")) {
                    v3 = cross(v1, v2, v3);
                    continue;
                } else {
                    printf("Unsupported 3-token operator\n");
                    continue;
                }
            } else { // not the clenest but need to initilieze token 5 if previous condition not met
                //token5 = strtok(NULL, " \n");
                strcpy(v1.name, token1);
            }

            /* 5 Tok Assignment (ex: a = 1, 2, 3) */
            if (!strcmp(token2, "=") && (strstr(operations, token4) == NULL) && (token5 != NULL)) { //token 4 or 3
                Vector search = find(token1);
                // name not in list, add new to list
                if (strcmp(search.name, "NULL") == 0){ 
                    v1 = create(token1, atof(token3), atof(token4), atof(token5));
                    printf("Initializing Vector..\n");
                    insert(v1);  
                    printf("%s: (%.3f, %.3f, %.3f) \n", v1.name, v1.x, v1.y, v1.z);
    
                // already exists, overwrite vector
                } else { 
                    printf("Overwriting...\n");
                    v1 = create(token1, atof(token3), atof(token4), atof(token5));
                    insert(v1);
                }
            }
            /* 5 Tok Arithmetic (ex: c = a + b) */
            else if ((strstr(operations, token2) != NULL || strstr(operations, token4) != NULL) && token5 != NULL) {
                
                strcpy(v2.name, token3); 
                strcpy(v3.name, token5);  

                if(!strcmp(token2, "+") || !strcmp(token4, "+")){ // add
                    if(!strcmp(token2, "+")){ //a + b = c
                        v1 = find(v1.name);
                        v2 = find(v2.name);
                        v3 = add(v1, v2, v3);
                        insert(v3);
                    } else if(!strcmp(token4, "+")){ // a = b + c
                        v2 = find(v2.name);
                        v3 = find(v3.name);
                        v1 = add(v2, v3, v1); 
                        insert(v1);
                    } 
                
                }else if(!strcmp(token2, "-") || !strcmp(token4, "-")){ //sub
                    if(!strcmp(token2, "-")){ //a - b = c  
                        v1 = find(v1.name);
                        v2 = find(v2.name);
                        v3 = sub(v1, v2, v3); 
                        insert(v3);
                    } else if(!strcmp(token4, "-")){ // a = b - c
                        v2 = find(v2.name);
                        v3 = find(v3.name);
                        v1 = sub(v2, v3, v1);
                        insert(v1);
                    }

                } else if(!strcmp(token2, "*")){ // scalar mult  
                    if (isdigit(*token5)){ // c = a * 5
                        v2 = find(token3);
                        v3 = scalar_mult(v2, atof(token1), v3);
                        insert(v3);
                    } else if (isdigit(*token3)){ // c = 5 * a
                        v1 = find(token5);
                        v3 = scalar_mult(v1, atof(token3), v3);
                        insert(v3);
                    } 

                } else if(!strcmp(token2, "x") || !strcmp(token4, "x")){
                        if (!strcmp(token2, "x")){ // a x b = c
                            v1 = find(token1);  
                            v2 = find(token3);
                            v3 = cross(v1, v2, v3);
                            insert(v3);
                        } else { // d = a x b (token4 is "x")
                            v2 = find(token3);
                            v3 = find(token5);
                            v1 = cross(v2, v3, v1);
                            insert(v1);
                        }
                        
                }
            } else {
                printf("TOKEN 2 TEST: %s\n", token2);
                printf("Invalid input\n");
                continue;
            }
        }
    }

    return 0;

}

#include "defs.h"

/*
  Function:  initPatronArray
  Purpose:   initializes a PatronArrayType structure with an allocated array and sets initial values
      out:   pointer to a PatronArrayType structure arr to be initialized
   return:   none
*/
void initPatronArray(PatronArrayType *arr){
    arr->elements = (PatronType*) malloc(sizeof(PatronType) * MAX_CAP);
    arr->size = 0;
    arr->nextId = PATRON_IDS;
}

/*
  Function:  addPatron
  Purpose:   adds a patron to a PatronArrayType structure
      in:   pointer to a PatronArrayType structure arr to where the patron will be added
      in:   pointer to a character array n pointing to the name of the patron that will be added
   return:   none
*/
void addPatron(PatronArrayType *arr, char *n){
    arr->elements[arr->size].id = arr->nextId;
    strcpy(arr->elements[arr->size].name, n);
    arr->nextId++;
    arr->size++;
}

/*
  Function:  findPatron
  Purpose:   finds a patron in a PatronArrayType structure based on the provided ID
      in:   pointer to a PatronArrayType structure arr to search through 
      in:   integer id representing the ID of the patron that will be be found
   in/out:   pointer to a PatronType pointer p which will point to the found patron
   return:   C_OK if the patron is found successfully, C_NOK if not found
*/
int findPatron(PatronArrayType *arr, int id, PatronType **p){
    for(int i = 0; i < arr->size; i++){
        if(arr->elements[i].id == id){
            *p = &(arr->elements[i]);
            return C_OK;
        }
    }
    return C_NOK;
}

/*
  Function:  printPatrons
  Purpose:   prints the details of all patrons in a PatronArrayType structure
      in:   pointer to a PatronArrayType structure arr that will be printed
   return:   none
*/
void printPatrons(PatronArrayType *arr){
    for (int i = 0; i < arr->size; i++) {
        printf("Patron #%d %s\n", arr->elements[i].id, arr->elements[i].name);
    }
}

/*
  Function:  cleanupPatronArray
  Purpose:   frees the allocated memory for the array in a PatronArrayType structure
      in:   pointer to a PatronArrayType structure arr that will be cleaned up
   return:   none
*/
void cleanupPatronArray(PatronArrayType *arr){
    free(arr->elements);
}

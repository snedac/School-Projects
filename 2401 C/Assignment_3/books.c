#include <stdio.h>
#include <string.h>

#include "defs.h"

/*
  Function:  initBook
  Purpose:   initializes a BookType structure with the provided data
      out:   pointer to a BookType structure b containing book information
       in:   id of the book, title, author, publication year, and rating
   return:   none
*/
void initBook(BookType *b, int id, char *t, char *a, int y, float r){
    b->id = id;
    strcpy(b->title, t);
    strcpy(b->author, a);
    b->year = y;
    b->rating = r;
}

/*
  Function:  initBookArray
  Purpose:   initializes a BookArrayType structure with the specified order
      out:   pointer to a BookArrayType structure arr to be initialized
       in:   specified order for sorting the books
   return:   none
*/
void initBookArray(BookArrayType *arr, OrderType o){
    for(int i = 0; i < MAX_CAP; i++){
        arr->elements[i] = NULL;
    }
    arr->size = 0;
    arr->order = o;
}

/*
  Function:  addBookToArray
  Purpose:   adds a book to a BookArrayType structure in relation to the given order
      in:   pointer to a BookArrayType structure arr to which the book will be added
      in:   pointer to a BookType structure b containing the book to be added
     out:  pointing to the insertion point for the book through a pointer to an integer insPt
   return:   C_OK if the book is successfully added, C_NOK if the array is full
*/
int addBookToArray(BookArrayType *arr, BookType *b){
	int insPt = 0;
	
	if(arr->size == MAX_CAP){
		return C_NOK;
	}
	
	findInsPt(arr, b, &insPt);
	
	for(int i = arr-> size; i >= insPt; i--){
		if(i == insPt){
			arr->elements[i] = b;
		}
		else{
			arr->elements[i] = arr->elements[i - 1];
		}
	}
	
	arr->size++;
	
	return C_OK;
}

/*
  Function:  findInsPt
  Purpose:   finds the insertion point for a book in a BookArrayType structure based on its order
       in:   pointer to a BookArrayType structure arr to search within
      in:   pointer to a BookType structure b which points to the book that will be inserted
   in/out:   pointer to an integer insPt which will hold the insertion point value
   return:   C_OK if the insertion point is found successfully
*/
int findInsPt(BookArrayType *arr, BookType *b, int *insPt){
	int comapreTitle = 0;
	
	for(int i = 0; i < arr -> size; i++){
		int cmpBooks = strcmp(arr->elements[i]->author, b->author);
		
		if(arr->order == ORDER_BY_AUTHOR){
			if(cmpBooks == 0){
				cmpBooks = strcmp(arr->elements[i]->title, b->title); 
			}
			if(cmpBooks > 0){
				*insPt = i;
				return C_OK;
			}
		}
		else if(arr->order == ORDER_BY_RATING){
			if(b -> rating > arr->elements[i]->rating){
				*insPt = i;
				return C_OK;
			}
		}
	}
	
	*insPt = arr->size;
	return C_OK;
}

/*
  Function:  printBook
  Purpose:   prints the details of a book
       in:   pointer to a BookType structure b holding the books that will be printed
   return:   none
*/
void printBook(BookType *b){
	printf("%d : %-64s : %-30s : %4d : %.2f\n", b->id, b->title, b->author, b->year, b->rating);
}

/*
  Function:  printBookArray
  Purpose:   prints all the books within BookArrayType
       in:   pointer to a BookArrayType structure arr holding the books that will be printed
   return:   none
*/
void printBookArray(BookArrayType *arr){
	for(int i = 0; i < arr->size; i++){
		printBook(arr->elements[i]);
	}
}

/*
  Function:  cleanupBookArray
  Purpose:   deallocates memory for all the books within a BookArrayType structure
       in:   pointer to a BookArrayType structure arr to be deallocated
   return:   none
*/
void cleanupBookArray(BookArrayType *arr){
	for(int i = 0; i < arr->size; i++){
		free(arr->elements[i]);
	}
}

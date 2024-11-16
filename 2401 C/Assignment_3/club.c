#include <stdio.h>
#include <string.h>

#include "defs.h"

/*
  Function:  initBookClub
  Purpose:   initializes a BookClubType structure with the provided name and a default order of by author
   in/out:   pointer to a BookClubType structure club which will be initialized
       in:   pointer to a string n the name of the book club
   return:   none
*/
void initBookClub(BookClubType *club, char *n){
    initBookArray(&(club->books), ORDER_BY_AUTHOR);
    strcpy(club->name,n);
}

/*
  Function:  addBookToClub
  Purpose:   adds a new book to a book club's book array
  in/out:   pointer to a BookClubType structure club where the book will be added
      in:   id, title, author's first name, author's last name, publication year, and rating
   return:   C_OK if the book is successfully added, C_NOK if it is not
*/
int  addBookToClub(BookClubType *club, int id, char *t, char *af, char *al, int y, float r){
	char name[MAX_STR];
	int result = 0;
	
    if(id < 0 || y < 0){
    	return C_NOK;
    }
    if(r < 0.00 || r > 5.00){
    	return C_NOK;
    }
    
    sprintf(name, "%s, %s", al, af);
    
    BookType *newBook = (BookType *)malloc(sizeof(BookType));
    
    initBook(newBook, id, t, name, y, r);
    
    result = addBookToArray(&(club->books), newBook);
    
    if(result == C_NOK){
    	free(newBook);
    	return C_NOK;
    }
    
    return C_OK;
}

/*
  Function:  printBooks
  Purpose:   prints all the books in a book club's structure
       in:   pointer to a BookClubType structure club
   return:   none
*/
void printBooks(BookClubType *club){
	printf("Books for %s:\n", club->name);
	printBookArray(&(club->books));
}


/*
  Function:  printTopRatedBooks
  Purpose:   prints the top 20% top-rated books in a book club's collection
       in:   pointer to a BookClubType structure club representing the book club
      out:	 the temporary structure topRatedBooks containing the top 20% top-rated books
   return:   none
*/
void printTopRatedBooks(BookClubType *club){
    BookArrayType allBooks;
    BookArrayType topRatedBooks;

    initBookArray(&allBooks, ORDER_BY_RATING);
    initBookArray(&topRatedBooks, ORDER_BY_RATING);
    
	for(int i = 0; i < club->books.size; i++){
		addBookToArray(&(allBooks),club->books.elements[i]);
	}
	
	int topRated = allBooks.size * 0.2;
	
	for(int i = 0; i < topRated; i++){
		addBookToArray(&(topRatedBooks), allBooks.elements[i]);
	}
	
	printBookArray(&(topRatedBooks));
}







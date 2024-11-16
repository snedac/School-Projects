#include <stdio.h>
#include <string.h>

#include "defs.h"

int main()
{
  	BookClubType club;
    char clubName[MAX_STR] = "Book Club";


    initBookClub(&club, clubName);
    loadBookData(&club);
    
    int choice = 1;
    int result = 1;
    
    while(1){
    
    	printMenu(&choice);
    	
    	if(choice == 1){
    		printBooks(&club);
    	}
    	
    	if(choice == 2){
    		printTopRatedBooks(&club);
    	}
    	
    	if(choice == 3){
    		int id;
    		char title[MAX_STR];
    		char author[MAX_STR];
        	char first[MAX_STR];
        	char last[MAX_STR];
        	int year;
        	float rating;    		
    	

    		printf("Enter book id: ");
    		scanf("%d", &id);
    		
    		printf("Enter title: ");
    		scanf(" %[^\n]", title);
    		
        	printf("Enter author's first and last name: ");
        	scanf(" %[^\n]", author);
        	sscanf(author, "%s %s", first, last);
    		
    		printf("Enter publication year: ");
    		scanf("%d", &year);
    		
    		printf("Enter rating: ");
    		scanf("%f", &rating);
    		
    		result = addBookToClub(&club, id, title, first, last, year, rating);
    		
    		if(result == C_OK){
    			printf("Book was successfully added\n");
    		}
    		
    		else{
    			printf("Error:  book could not be added\n");
    		}
    		
    	}
    	
    	if(choice == 0){
				break;
    	}
    	
    }
    
    cleanupBookArray(&(club.books));
    

	return(0);
}


/*
  Function: printMenu
  Purpose:  prints the main menu as well as saves the choice the user inputs for what action they would like to perform 
      in/out:   pointer to the integer choice which stores the user's selection
   return:  nothing
*/
void printMenu(int *choice)
{
  int c = -1;
  int numOptions = 3;

  printf("\nMAIN MENU\n");
  printf("  (1) Print all books\n");
  printf("  (2) Print top rated books\n");
  printf("  (3) Add a book\n");
  printf("  (0) Exit\n\n");

  printf("Please enter your selection: ");
  scanf("%d", &c);

  if (c == 0) {
    *choice = c;
    return;
  }

  while (c < 0 || c > numOptions) {
    printf("Please enter your selection: ");
    scanf("%d", &c);
  }

  *choice = c;
}


#include <stdio.h>
#include <string.h>

#include "defs.h"

int main()
{ 

  RestaurantType restaurant;

 
  initRestaurant(&restaurant, "Caden's Bistro");


  loadPatronData(&restaurant);
  loadResData(&restaurant);

  int choice;

  while(1){
    printMenu(&choice);

      if (choice == 1) {
 
        printf("REGISTERED PATRONS at %s:\n", restaurant.name);
        printPatrons(&restaurant.patrons);
      } 
      else if (choice == 2) {
        printf("RESERVATIONS at %s:\n", restaurant.name);
        printReservations(&restaurant.reservations);
      } 
      else if (choice == 3) {
        int pId;
        printf("Enter Patron ID: ");
        scanf("%d", &pId);
        printf("RESERVATIONS BY PATRON at %s:\n", restaurant.name);
        printResByPatron(&restaurant, pId);
      } 
      else if (choice == 0) {
        break;
      } 
    }

  cleanupRestaurant(&restaurant);
  return(0);
}

void printMenu(int *choice)
{
  int c = -1;
  int numOptions = 3;

  printf("\nMAIN MENU\n");
  printf("  (1) Print patrons\n");
  printf("  (2) Print reservations\n");
  printf("  (3) Print reservations by patron\n");
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


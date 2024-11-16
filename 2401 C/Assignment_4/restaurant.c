#include "defs.h"

/*
  Function:  initRestaurant
  Purpose:   initializes a RestaurantType structure with the provided name and initializes internal data structures
      out:   pointer to a RestaurantType structure r to be initialized
      in:    pointer to a character array n containing the name of the restaurant
   return:   none
*/
void initRestaurant(RestaurantType *r, char *n){
    strcpy(r->name,n);
    initPatronArray(&(r->patrons));
    initResvList(&(r->reservations));
}

/*
  Function:  createResv
  Purpose:   creates a reservation in a RestaurantType structure based on patron ID and reservation details
      in:   pointer to a RestaurantType structure r in which the reservation will be created
      in:   integer pId representing the ID of the patron making the reservation
      in:   integers yr, mth, day, hr, min representing the date and time of the reservation
   return:   none
*/
void createResv(RestaurantType *r, int pId, int yr, int mth, int day, int hr, int min){
    int result = 0;
    result = validateResvTime(yr, mth, day, hr, min);

    if(result == C_NOK){
        printf("ERROR: Date %d-%d-%d or time %d:%d is invalid\n", yr, mth, day, hr, min);
        return;
    }

    PatronType *foundPatron;
    result = findPatron(&(r->patrons), pId, &foundPatron);


    if(result == C_NOK){
        printf("ERROR: Patron id %d was not found\n", pId);
        return;
    }

    ResvTimeType *resvTime;
    initResvTime(&resvTime, yr, mth, day, hr, min);

    ResvType *reservation;
    initResv(&reservation, foundPatron, resvTime);

    addResv(&(r->reservations), reservation);
}

/*
  Function:  printResByPatron
  Purpose:   prints reservations in a RestaurantType structure based on patron ID
      in:   pointer to a RestaurantType structure r to search through
      in:   integer id representing the ID of the patron
   return:   none
*/
void printResByPatron(RestaurantType *r, int id){
    NodeType *currNode = r->reservations.head;

    while (currNode != NULL) {
        if (currNode->data->patron->id == id) {
            printReservation(currNode->data);
        }
        currNode = currNode->next;
    }

}

/*
  Function:  cleanupRestaurant
  Purpose:   cleans up memory allocated for internal data structures in a RestaurantType structure
      in:   pointer to a RestaurantType structure r that will be cleaned up
   return:   none
*/
void cleanupRestaurant(RestaurantType *r){
    cleanupPatronArray(&(r->patrons));
    cleanupResvList(&(r->reservations));
}

/*
  Function:  validateResvTime
  Purpose:   validates the provided date and time for a reservation
      in:   integers yr, mth, day, hr, min representing the date and time to be validated
   return:   C_OK if the date and time are valid, C_NOK if not valid
*/
int validateResvTime(int yr, int mth, int day, int hr, int min){
    if(yr < 2023){
        return C_NOK;
    }
    if(mth > 12){
        return C_NOK;
    }
    if(day > 31){
        return C_NOK;
    }
    if(hr > 23){
        return C_NOK;
    }
    if(min > 59){
        return C_NOK;
    }

    return C_OK;
}

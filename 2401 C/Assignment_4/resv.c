#include "defs.h"

/*
  Function:  initResvList
  Purpose:   initializes a ResvListType structure with initial values
      out:   pointer to a ResvListType structure list that will be initialized
   return:   none
*/
void initResvList(ResvListType *list){
    list->head = NULL;
    list->nextId = RES_IDS; 
}

/*
  Function:  initResv
  Purpose:   initializes a ResvType structure with the provided patron and reservation time
      in:   double pointer to a ResvType structure r that will be initialized
      in:   pointer to a PatronType structure p representing the patron making the reservation
      in:   pointer to a ResvTimeType structure rt representing the reservation time
   return:   none
*/
void initResv(ResvType **r, PatronType *p, ResvTimeType *rt){
    ResvType *tmpRes;
    tmpRes = (ResvType*)malloc(sizeof(ResvType));

    tmpRes->id = 0;
    tmpRes->patron = p;
    tmpRes->resvTime = rt;

    *r = tmpRes;
} 

/*
  Function:  initResvTime
  Purpose:   initializes a ResvTimeType structure with the provided date and time values
      in:   double pointer to a ResvTimeType structure rt that will be initialized
      in:   integers yr, mth, day, hr, min representing the date and time of the reservation
   return:   none
*/
void initResvTime(ResvTimeType **rt, int yr, int mth, int day, int hr, int min){
    ResvTimeType *tmpRt;
    tmpRt = (ResvTimeType*)malloc(sizeof(ResvTimeType));

    tmpRt->year = yr;
    tmpRt->month = mth;
    tmpRt->day = day;
    tmpRt->hours = hr;
    tmpRt->minutes = min;

    *rt = tmpRt;
}

/*
  Function:  addResv
  Purpose:   adds a reservation to a ResvListType structure in sorted order based on reservation time
      in:   pointer to a ResvListType structure list through which the reservation will be added
      in:   pointer to a ResvType structure r representing the reservation that will be added
   return:   none
*/
void addResv(ResvListType *list, ResvType *r){
    NodeType *newNode;
    NodeType *currNode;
    NodeType *prevNode;

    newNode = malloc(sizeof(NodeType));
    newNode->data = r;
    newNode->next = NULL;
    newNode->prev = NULL;

    newNode->data->id = list->nextId;
    list->nextId++; 

    currNode = list->head;
    prevNode = NULL;
    
    int result = 0; 
    while(currNode != NULL){
        result = lessThan(newNode->data->resvTime, currNode->data->resvTime);
        if(result == C_TRUE){
            break;
        }

        prevNode = currNode;
        currNode = currNode->next;
    }

    if(prevNode == NULL){
        list->head = newNode;
    }
    else{
        prevNode->next = newNode;
        newNode->prev = prevNode;
    }

    newNode->next  = currNode;

    if (currNode != NULL) {
        currNode->prev = newNode;
    }
}

/*
  Function:  lessThan
  Purpose:   compares two ResvTimeType structures to determine if the first is less than the second
      in:   pointer to a ResvTimeType structure r1 that will be compared
      in:   pointer to a ResvTimeType structure r2 that will be compared
   return:   C_TRUE if r1 is less than r2, C_FALSE otherwise
*/
int lessThan(ResvTimeType *r1, ResvTimeType *r2){
    if(r1->year < r2->year){
        return C_TRUE;
    }
    else if(r1->month < r2->month){
        return C_TRUE;
    }
    else if(r1->day < r2->day){
        return C_TRUE;
    }
    else if(r1->hours < r2->hours){
        return C_TRUE;
    }
    else if(r1->hours <= r2->hours && r1->minutes < r2->minutes){
        return C_TRUE;
    }

    return C_FALSE;
}

/*
  Function:  printReservation
  Purpose:   prints the details of a reservation
      in:   pointer to a ResvType structure r representing the reservation that will be printed
   return:   none
*/
void printReservation(ResvType *r){
    printf("%d :: %04d-%02d-%02d :: %02d:%02d :: %s\n", r->id, r->resvTime->year, r->resvTime->month, r->resvTime->day, r->resvTime->hours, r->resvTime->minutes, r->patron->name);
}

/*
  Function:  printReservations
  Purpose:   prints the details of all reservations in a ResvListType structure, both forward and backward
      in:   pointer to a ResvListType structure list that will be printed
   return:   none
*/
void printReservations(ResvListType *list){
    NodeType *currNode = list->head;
    NodeType *prevNode = NULL;

    printf("--- FORWARD:\n");

    while(currNode != NULL){
        printReservation(currNode->data);
        prevNode = currNode;
        currNode = currNode->next;
    }

    printf("--- BACKWARD:\n");
    currNode = prevNode;
    while(currNode != NULL){
        printReservation(currNode->data);
        currNode = currNode->prev;
    }
}

/*
  Function:  cleanupResvList
  Purpose:   frees the allocated memory for the nodes and associated data in a ResvListType structure
      in:   pointer to a ResvListType structure list that will be cleaned up
   return:   none
*/
void cleanupResvList(ResvListType *list){
  NodeType *currNode = list->head;
  NodeType *nextNode;

  while (currNode != NULL) {
    nextNode = currNode->next;
    free(currNode->data->resvTime);
    free(currNode->data);
    free(currNode);
    currNode = nextNode;
  }
}

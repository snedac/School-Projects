#include "defs.h"

/*
  Function:  initHollow
  Purpose:   Initialize the hollow structure, placing walls, characters, and flyers at their respective positions.
       in:   pointer to the EscapeType structure containing information about heroes and flyers
       out:  2D array representing the hollow structure
*/
void initHollow(EscapeType* escape, char hollow[][MAX_COL]){
    for (int j = 0; j < MAX_COL; j++) {
        hollow[0][j] = '-';
        hollow[MAX_ROW - 1][j] = '-';
    }

    for (int i = 1; i < MAX_ROW - 1; i++) {
        hollow[i][0] = '|';
        for (int j = 1; j < MAX_COL - 1; j++) {
            if(i == MAX_ROW - 1){
                break;
            }
            hollow[i][j] = ' ';
        }
        hollow[i][MAX_COL - 1] = '|';
    }

    hollow[MAX_ROW - 2][0] = '=';
    hollow[MAX_ROW -2][MAX_COL - 1] = '=';

    for (int i = 0; i < escape->flyers.size; i++) {
        int result = flyerIsDone(escape->flyers.elements[i]);
        if(result == C_FALSE){
            hollow[escape->flyers.elements[i]->partInfo.pos.row][escape->flyers.elements[i]->partInfo.pos.col] = escape->flyers.elements[i]->partInfo.avatar;
        }
    }

    for (int i = 0; i < escape->heroes.size; i++) {
        int result = heroIsSafe(escape->heroes.elements[i]);
        if(result == C_FALSE){
            hollow[escape->heroes.elements[i]->partInfo.pos.row][escape->heroes.elements[i]->partInfo.pos.col] = escape->heroes.elements[i]->partInfo.avatar;
        }
    }
}

/*
  Function:  serializeHollow
  Purpose:   Serialize the hollow, including information about heroes and their health, for display.
       in:   pointer to the EscapeType structure containing information about heroes and flyers
       out:  character array containing the serialized hollow structure
*/
void serializeHollow(EscapeType* escape, char* serializedHollow) {
    int count = 0;
    char hollow[MAX_ROW][MAX_COL];

    initHollow(escape, hollow);

    int index = 0;
    for (int i = 0; i < MAX_ROW; i++) {
        for (int j = 0; j < MAX_COL; j++) {
            serializedHollow[index++] = hollow[i][j];
        }
        if(i >= MAX_ROW - 3){
            if (count < escape->heroes.size) {
                int health = escape->heroes.elements[count]->health;

                char* name = escape->heroes.elements[count]->name;

                snprintf(&serializedHollow[index], MAX_COL, "  %s: %d", name, health);
                
                index += snprintf(NULL, 0, "  %s: %d", name, health);
            }
            count++;
        }

        serializedHollow[index++] = '\n';
    }
    serializedHollow[index] = '\0';
}

/*
  Function:  outputHollow
  Purpose:   Output the serialized hollow to the standard output and send it to the connected view socket.
       in:   pointer to the EscapeType structure containing information about heroes and flyers
*/
void outputHollow(EscapeType* escape) {
    char serializedHollow[MAX_ROW * (MAX_COL + 10)]; 

    serializeHollow(escape, serializedHollow);

    printf("%s", serializedHollow);

    sendData(escape->viewSocket, serializedHollow);
}
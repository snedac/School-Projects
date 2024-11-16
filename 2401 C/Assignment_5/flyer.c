#include "defs.h"

/*
  Function:  spawnFlyer
  Purpose:   Spawn a flyer with the specified avatar, row, column, and strength values.
       in:   pointer to the EscapeType structure containing information about the escape
       in:   avatar character, row and column positions, and strength value for the new flyer
*/
void spawnFlyer(EscapeType* escape, char avatar, int row, int column, int strength){
    FlyerType* newFlyer = (FlyerType*)malloc(sizeof(FlyerType));

    newFlyer->partInfo.avatar = avatar;
    setPos(&(newFlyer->partInfo.pos), column, row);
    newFlyer->strength = strength;
    escape->flyers.elements[escape->flyers.size] = newFlyer;
    escape->flyers.size++;   
}

/*
  Function:  moveFlyer
  Purpose:   Move a flyer based on its avatar and a random number, and check for collisions with heroes.
       in:   pointer to the FlyerType structure to be moved
       in:   pointer to the EscapeType structure containing information about the escape
*/
void moveFlyer(FlyerType* flyer, EscapeType* escape){
    int result = flyerIsDone(flyer);
    int col = 0;
    int row = 0;
    if(result == C_FALSE){
        if(flyer->partInfo.avatar == 'v'){
            row += 1;
            int move = randomInt(3) - 1;
            col += move;
        }
        if(flyer->partInfo.avatar == '@'){
            int verticalMove = randomInt(7) - 3;
            row += verticalMove;

            int horizontalMove = randomInt(3) + 1;

            int result = 0;

            computeHeroDir(escape, flyer, &result);
            col += result * horizontalMove;
        }

        setPos(&(flyer->partInfo.pos), col, row); 
    }

    HeroType* collidedHero = checkForCollision(&(flyer->partInfo.pos), escape);

    if(collidedHero != NULL && heroIsSafe(collidedHero) == C_FALSE){
        incurDamage(collidedHero, flyer);
    }
}

/*
  Function:  computeHeroDir
  Purpose:   Compute the direction for a flyer to move based on the positions of heroes in the escape.
       in:   pointer to the EscapeType structure containing information about heroes and flyers
       in:   pointer to the FlyerType structure for which the direction is to be computed
       out:  pointer to an integer to store the computed direction value
*/
void computeHeroDir(EscapeType* escape, FlyerType* flyer, int* result){
    int HDis = 0;
    int TDis = 0;
    int harold = 0;
    int timmy = 0;
    int skip = 0;

    for(int i = 0; i < escape->heroes.size; i++){
        int currHero = escape->heroes.elements[i]->partInfo.avatar;
        if(currHero == 'H'){
            harold = escape->heroes.elements[i]->partInfo.pos.col;
        }
        if(currHero == 'T'){
            timmy = escape->heroes.elements[i]->partInfo.pos.col;
        }
    }

    HDis = harold - flyer->partInfo.pos.col;
    TDis = timmy - flyer->partInfo.pos.col;


    for(int i = 0; i < escape->heroes.size; i++){

       if(strcmp(escape->heroes.elements[i]->name, "Timmy") == 0){
            if(escape->heroes.elements[i]->dead == C_TRUE || heroIsSafe(escape->heroes.elements[i]) == C_TRUE){
                if(HDis < 0){
                    *result = DIR_LEFT;
                }
                if(HDis > 0){
                    *result = DIR_RIGHT;
                }
                else{
                    *result =  DIR_SAME;
                }
                skip = 1;
            }
       } 

        if(strcmp(escape->heroes.elements[i]->name, "Harold") == 0){
            if(escape->heroes.elements[i]->dead == C_TRUE || heroIsSafe(escape->heroes.elements[i]) == C_TRUE){
                if(TDis < 0){
                    *result =  DIR_LEFT;
                }
                if(TDis > 0){
                    *result =  DIR_RIGHT;
                }
                else{
                    *result =  DIR_SAME;
                }
                skip = 1;
            }
       } 
    }

    if(skip != 1){
        if(HDis < 0 && TDis < 0){
            *result = DIR_LEFT;
        }
        else if(TDis > 0 && HDis > 0){
            *result = DIR_RIGHT ;
        }
        else {
            if(abs(HDis) < abs(TDis)) {
                if (HDis < 0) {
                    *result = DIR_LEFT;
                } 
                else {
                    *result = DIR_RIGHT ;
                }
            } 
            else if (abs(TDis) < abs(HDis)) {
                if (TDis < 0) {
                    *result = DIR_RIGHT ;
                } 
                else {
                    *result = DIR_LEFT;
                }
            }
            else {
                *result = DIR_SAME;
            }
        }

    }
}

/*
  Function:  checkForCollision
  Purpose:   Check for collisions between a flyer and heroes at a given position.
       in:   pointer to the PositionType structure representing the position to check
       in:   pointer to the EscapeType structure containing information about the escape scenario
   return:   pointer to the HeroType structure if a collision is detected, NULL otherwise
*/
HeroType* checkForCollision(PositionType* pos, EscapeType* escape){
    for(int i = 0; i < escape->heroes.size; i++){
        if(escape->heroes.elements[i]->partInfo.pos.row == pos->row && escape->heroes.elements[i]->partInfo.pos.col == pos->col){
            return escape->heroes.elements[i];
        }
    }
    return NULL;
}

/*
  Function:  flyerIsDone
  Purpose:   Check if a flyer has reached the maximum row position.
       in:   pointer to the FlyerType structure to be checked
   return:   C_TRUE if the flyer has reached the maximum row position, C_FALSE otherwise
*/
int  flyerIsDone(FlyerType* flyer){
    if(flyer->partInfo.pos.row >= MAX_ROW - 1){
        return C_TRUE;
    }
    return C_FALSE;
}
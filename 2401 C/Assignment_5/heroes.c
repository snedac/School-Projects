#include "defs.h"

/*
  Function:  initHero
  Purpose:   Initialize a hero with the provided avatar, health, and name.
       out:  pointer to the initialized HeroType structure
       in:   avatar character, health value, and hero name string
*/
void initHero(HeroType** h, char avatar, int health, char* heroName) {
    *h = (HeroType*)malloc(sizeof(HeroType));

    (*h)->partInfo.avatar = avatar;
    (*h)->health = health;
    (*h)->dead = C_FALSE;

    strcpy((*h)->name, heroName);

    (*h)->partInfo.pos.col = 0;
    (*h)->partInfo.pos.row = 0;

    int row = MAX_ROW - 2;
    int col = randomInt(4) + 1;
    setPos(&((*h)->partInfo.pos), col, row);
}

/*
  Function:  addHero
  Purpose:   Add a hero to the HeroArrayType structure.
       in:   pointer to the HeroArrayType structure
       in:   pointer to the HeroType structure to be added
*/
void addHero(HeroArrayType* heroArr, HeroType* h){
    heroArr->elements[heroArr->size] = h;
    heroArr->size++;
}

/*
  Function:  moveHero
  Purpose:   Move a hero based on its avatar and a random number.
       in:   pointer to the HeroType structure to be moved
       in:   pointer to the EscapeType structure containing information about the escape scenario
*/
void moveHero(HeroType* hero, EscapeType* escape){
    int num = randomInt(100);
    int result = heroIsSafe(hero);
    int col = 0;
    int row = 0;
    if(hero->dead == C_FALSE && result == C_FALSE){
        if(hero->partInfo.avatar == 'T'){
            if(num < 50){
                col += 2;
            }
            else if(num >= 50 && num < 80){
                col -= 1;
            }
            else{
                col += 1;
            }
        }
        else if(hero->partInfo.avatar  == 'H'){
            if(num < 10){
                col += 5;
            }
            else if(num >= 10 && num < 20){
                col -= 4;
            }
            else if(num >= 20 && num < 60){
                col += 3;
            }
            else if(num >= 60 && num < 80){
                col -= 2;
            }
            else{
                col = 0;
            }
        }

        setPos(&(hero->partInfo.pos), col, row);
    }
}

/*
  Function:  setPos
  Purpose:   Set the position of a character in the hollow based on the specified column and row values.
       in:   pointer to the PositionType structure to be modified
       in:   column and row values to set
*/
void setPos(PositionType* pos, int col, int row){
    pos->col += col;
    pos->row += row;

    if(pos->col >= MAX_COL - 1){
        pos->col = MAX_COL - 2;
    }
    if(pos->col <= 0){
        pos->col = 1;
    }
    if(pos->row >= MAX_ROW - 1){
        pos->row = MAX_ROW - 1;
    }
    if(pos->row <= 0){
        pos->row = 1;
    }
}

/*
  Function:  incurDamage
  Purpose:   Inflict damage on a hero based on the strength of a flyer.
       in:   pointer to the HeroType structure to receive damage
       in:   pointer to the FlyerType structure causing the damage
*/
void incurDamage(HeroType* hero, FlyerType* flyer){
    hero->health -= flyer->strength;
    if(hero->health <= 0){
        hero->health = 0;
        hero->dead = C_TRUE;
        hero->partInfo.avatar = '+';
    }
}

/*
  Function:  heroIsSafe
  Purpose:   Check if a hero is safe by comparing its column position with the maximum column value.
       in:   pointer to the HeroType structure to be checked
   return:   C_TRUE if the hero is safe, C_FALSE otherwise
*/
int heroIsSafe(HeroType* hero){
    if(hero->partInfo.pos.col >= MAX_COL - 2){
        return C_TRUE;
    }
    else{
        return C_FALSE;
    }
}
#include "defs.h"

/*
  Function:  initEscape
  Purpose:   Initialize the escape scenario by setting up the server socket, creating initial heroes, and accepting connections.
       in:   pointer to the EscapeType structure to be initialized
*/
void initEscape(EscapeType* escape){
    srand(time(NULL));

    escape->heroes.elements = (HeroType**)malloc(sizeof(HeroType*) * MAX_ARR);
    escape->heroes.size = 0;

    escape->flyers.size = 0;

    setupServerSocket(&(escape->listenSocket));
    acceptConnection(escape->listenSocket, &(escape->viewSocket));

    HeroType* timmy;
    initHero(&timmy, 'T', MAX_HEALTH, "Timmy");
    addHero(&(escape->heroes), timmy);

    HeroType* harold;
    initHero(&harold, 'H', MAX_HEALTH, "Harold");
    addHero(&(escape->heroes), harold);
}

/*
  Function:  escapeIsOver
  Purpose:   Check if the escape scenario is over by determining if all heroes have either escaped or died.
       in:   pointer to the EscapeType structure to be checked
   return:   C_TRUE if the escape scenario is over, C_FALSE otherwise
*/
int escapeIsOver(EscapeType* escape){
    int timmy = 0;
    int harold = 0;
    for(int i = 0; i < escape->heroes.size; i++){
        if(strcmp(escape->heroes.elements[i]->name, "Timmy") == 0){
            if(heroIsSafe(escape->heroes.elements[i]) == C_TRUE || escape->heroes.elements[i]->dead == C_TRUE){
                timmy = C_TRUE;
            }
        }
        if(strcmp(escape->heroes.elements[i]->name, "Harold") == 0){
            if(heroIsSafe(escape->heroes.elements[i]) == C_TRUE || escape->heroes.elements[i]->dead == C_TRUE){
                harold = C_TRUE;
            }
        }
    }

    if(timmy == C_TRUE && harold == C_TRUE){
        return C_TRUE;
    }
    else{
        return C_FALSE;
    }
}

/*
  Function:  cleanupEscape
  Purpose:   Clean up the resources used by the escape scenario, including closing sockets and freeing allocated memory.
       in:   pointer to the EscapeType structure to be cleaned up
*/
void cleanupEscape(EscapeType* escape) {
    close(escape->viewSocket);
    close(escape->listenSocket);

    for (int i = 0; i < escape->heroes.size; i++) {
        free(escape->heroes.elements[i]);
    }
    free(escape->heroes.elements);

    for (int i = 0; i < escape->flyers.size; i++) {
        free(escape->flyers.elements[i]);
    }
}

/*
  Function:  handleEscapeResult
  Purpose:   Handle the results of the escape scenario by printing messages for each hero based on their status.
       in:   pointer to the EscapeType structure containing the results
*/
void handleEscapeResult(EscapeType* escape) {
    for (int i = 0; i < escape->heroes.size; i++) {
        if (escape->heroes.elements[i]->dead == C_TRUE) {
            printf("%s IS DEAD...\n", escape->heroes.elements[i]->name);
        } 
        else if (heroIsSafe(escape->heroes.elements[i]) == C_TRUE) {
            printf("%s ESCAPED!\n", escape->heroes.elements[i]->name);
        }
    }
}

/*
  Function:  runEscape
  Purpose:   Run the escape scenario, continuously updating the state of heroes and flyers until the scenario is over.
*/
void runEscape() {
    EscapeType escape;
    initEscape(&escape);
    outputHollow(&escape);

    while (escapeIsOver(&escape) == C_FALSE) {
        system("clear");
        for (int i = 0; i < escape.heroes.size; i++) {
            moveHero(escape.heroes.elements[i], &escape); 
        }

        for (int i = 0; i < escape.flyers.size; i++) {
            moveFlyer(escape.flyers.elements[i], &escape); 
        }

        int spawnChance = randomInt(100);

        if(spawnChance < BIRD_SPAWN_RATE){
            int row = randomInt(5);
            int col = randomInt(MAX_COL - 3) + 1;
            int strength = randomInt(3) + 3;
            spawnFlyer(&escape, 'v', row, col, strength);
        }

        if(spawnChance < MONKEY_SPAWN_RATE){
            int row = randomInt(15);
            int col = randomInt(MAX_COL - 2) + 1;
            int strength = randomInt(4) + 8;
            spawnFlyer(&escape, '@', row, col, strength);
        }


        outputHollow(&escape);
        usleep(OUTPUT_INTERVAL);
    }

    handleEscapeResult(&escape);
    cleanupEscape(&escape);
}
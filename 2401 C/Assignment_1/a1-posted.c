#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MAX_ROW       15
#define MAX_COL       60
#define MAX_BIRDS    128
#define BIRD_FREQ     90

#define C_TRUE         1
#define C_FALSE        0

void initHollow(char[MAX_ROW][MAX_COL]);
void printHollow(char[MAX_ROW][MAX_COL]);
char escapeOver(char, char, int, int);
char isDone(char, int);
int  moveHero(char, int, char[MAX_ROW][MAX_COL]);
void moveBird(int, int[MAX_BIRDS], int[MAX_BIRDS], char[MAX_ROW][MAX_COL]);
void moveInHollow(char, int, int, int, int, char[MAX_ROW][MAX_COL]);
void printResult(char, char, int, int);
int  randomInt(int);

int avatarPos(char, char[MAX_ROW][MAX_COL]);
void start(char[MAX_ROW][MAX_COL]);
void moveBoth(int, int, char [MAX_ROW][MAX_COL]);


int main(){
 srand(time(NULL));
 //system("clear");
  
  
 char hollow[MAX_ROW][MAX_COL];
  
 int bottomRow = MAX_ROW - 2;

  
 initHollow(hollow);
  
 start(hollow);
 
 printHollow(hollow);
 printf("\n");
 	
	for(int i = 0; i < 10; i++){
	
	usleep(500000);
	
	int oldTCol = avatarPos('T', hollow);
	int oldHCol = avatarPos('H', hollow);

	moveBoth(oldTCol, oldHCol, hollow);
 	
 	}
 	
  return 0;
	
}

/*
  Function:  initHollow
  Purpose:   Initializes the hollow grid.
  Parameters:
    in:      2D character array representing the grid
*/
void initHollow(char hollow[MAX_ROW][MAX_COL]){
	int i, j;
    
  for (i = 0; i < MAX_ROW; i++) {
      for (j = 0; j < MAX_COL; j++) {
      
        if(i == 0 || i == (MAX_ROW - 1)){
        	hollow[i][j] = '-';
        }
        else if((j == 0 || j == MAX_COL - 1) && i < MAX_ROW - 2){
        	hollow[i][j] = '|';
        }
        else if(j == 0 || j == (MAX_COL - 1)){
          hollow[i][j] = '=';
        }
        else{
          hollow[i][j] = ' ';
        }
      }
  }


}

/*
  Function:  printHollow
  Purpose:   Prints the contents of the hollow grid.
  Parameters:
    in:      2D character array representing the grid
*/
void printHollow(char hollow[MAX_ROW][MAX_COL]){

	for (int i = 0; i < MAX_ROW; i++) {
  	for (int j = 0; j < MAX_COL; j++) {
    	printf("%c ", hollow[i][j]);
    }
    printf("\n");
	}

}

/*
  Function:  moveInHollow
  Purpose:   Moves an avatar within the hollow grid.
  Parameters:
    in:      avatar character ('T', 'B', or 'H')
    in:      oldRow, oldCol - previous position of the avatar
    in:      newRow, newCol - new position of the avatar
    in:      2D character array representing the grid
*/
void moveInHollow(char avatar, int oldRow, int oldCol, int newRow, int newCol, char hollow[MAX_ROW][MAX_COL]){

	printf("We are moving %c from position %d %d to position %d %d \n", avatar, oldRow, oldCol, newRow, newCol);
	
	if(avatar == 'T'){
		hollow[oldRow][oldCol] = ' ';
		hollow[newRow][newCol] = 'T';
	}
	if(avatar == 'B'){
		hollow[oldRow][oldCol] = ' ';
		hollow[newRow][newCol] = 'v';
	}
	if(avatar == 'H'){
		hollow[oldRow][oldCol] = ' ';
		hollow[newRow][newCol] = 'H';
	}
	
}


/*
  Function:  moveHero
  Purpose:   Moves an avatar (hero) within the hollow grid based on random rules.
  Parameters:
    in:      avatar character ('T' or 'H')
    in:      oldPos - previous position of the avatar
    in:      2D character array representing the grid
    return:  new position of the avatar
*/
int  moveHero(char avatar, int oldPos, char hollow[MAX_ROW][MAX_COL]){
	if(avatar == 'T'){
		int randNum = randomInt(100);

		if (randNum < 50) {
				return oldPos + 3;
		} 
		else if (randNum >= 50 && randNum < 70) {
				return oldPos - 2;
		} 
		else {
				return oldPos + 1;
		}
	}
	
	
	if(avatar == 'H'){
    int randNum = randomInt(100);

		if (randNum < 20) {
				return oldPos;
		} 
		else if (randNum >= 20 && randNum < 30) {
				return oldPos + 6;
		} 
		else if (randNum >= 30 && randNum < 40) {
				return oldPos - 4;
		} 
		else if (randNum >= 40 && randNum < 80) {
				return oldPos + 4;
		} 
		else {
				return oldPos - 2;
		}

	}
}


/*
  Function:  randomInt
  Purpose:   returns a random number in the range [0,max)
  Parameters:
    in:      maximum of range
    return:  randomly generated number
*/

int randomInt(int max)
{
  return(rand() % max);
}





//Helper Functions
/*
  Function:  moveBoth
  Purpose:   Moves both Tim and Har within the hollow grid.
  Parameters:
    in:      oldTCol - the previous column position of Tim
    in:      oldHCol - the previous column position of Har
    in/out:  hollow - 2D character array representing the grid
*/
void moveBoth(int oldTCol, int oldHCol, char hollow[MAX_ROW][MAX_COL]){
	int bottomRow = MAX_ROW - 2;

	int timMove = moveHero('T', oldTCol, hollow);
	int harMove = moveHero('H', oldHCol, hollow);

  
  do{
  	if(timMove <= 0){
 			timMove = moveHero('T', oldTCol, hollow);
 		}
 		if(harMove <= 0){
 			harMove = moveHero('H', oldHCol, hollow);
 		}
 		if(timMove == harMove){
 			timMove = moveHero('T', oldTCol, hollow);
			harMove = moveHero('H', oldHCol, hollow);
 		}
  
  }while(harMove <= 0 || timMove <= 0 || timMove == harMove);
   
  moveInHollow('T', bottomRow, oldTCol, bottomRow, timMove, hollow);
  moveInHollow('H', bottomRow, oldHCol, bottomRow, harMove, hollow);
 	
 	printHollow(hollow);
 	printf("\n");
 	
}


/*
  Function:  avatarPos
  Purpose:   Finds the column position of the given avatar in the hollow grid.
  Parameters:
    in:      avatar - the character representing the avatar ('T' or 'H')
    in:      hollow - 2D character array representing the grid
    return:  the column position of the avatar
*/
int avatarPos(char avatar, char hollow[MAX_ROW][MAX_COL]){

	if(avatar == 'T'){
		for (int j = 0; j < MAX_COL; j++) {
			if(hollow[MAX_ROW - 2][j] == 'T'){
				return j;
			}
		
		}
	}
	
	if(avatar == 'H'){
		for (int j = 0; j < MAX_COL; j++) {
			if(hollow[MAX_ROW - 2][j] == 'H'){
				return j;
			}
		
		}
	}

}



/*
  Function:  start
  Purpose:   Initializes and starts the game with Tim and Har in the hollow grid.
  Parameters:
    in/out:  hollow - 2D character array representing the grid
*/
void start(char hollow[MAX_ROW][MAX_COL]){

	int bottomRow = MAX_ROW - 2;
	
	int harMove = moveHero('H', 1, hollow);
 	int timMove = moveHero('T', 1, hollow); 	
 	
 	
 	
 	do{
  
  	if(timMove <= 0){
 			timMove = moveHero('T', 1, hollow);
 		}
 		if(harMove <= 0){
 			harMove = moveHero('H', 1, hollow);
 		}
 		if(timMove == harMove){
 			timMove = moveHero('T', 1, hollow);
			harMove = moveHero('H', 1, hollow);
 		}
  
  }while(harMove <= 0 || timMove <= 0 || timMove == harMove);
  
  moveInHollow('T', bottomRow, 1, bottomRow, timMove, hollow);
  moveInHollow('H', bottomRow, 1, bottomRow, harMove, hollow);
  
	
}


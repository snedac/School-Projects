#include "defs.h"

int main(int argc, char *argv[])
{
  if (argc == 1) {
    runEscape();
  } 
  else if (argc == 2) {
    char* serverIP = argv[1];
    viewEscape(serverIP);
  } 
  return 0;
}

int randomInt(int max)
{
  return(rand() % max);
}


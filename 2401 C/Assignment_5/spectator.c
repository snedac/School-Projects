#include "defs.h"

/*
  Function:  viewEscape
  Purpose:   View the ongoing escape by setting up a client socket and continuously receiving and displaying data.
       in:   IP address of the server hosting the escape
*/
void viewEscape(char* serverIP) {
    int clientSocket;
    char receivedData[MAX_BUFF];

    setupClientSocket(&clientSocket, serverIP);

    while (1) {
        rcvData(clientSocket, receivedData);

        if(!receivedData[0]){
            break;
        }

        system("clear");
        printf("%s", receivedData);
        usleep(OUTPUT_INTERVAL);
    }

    close(clientSocket);
}
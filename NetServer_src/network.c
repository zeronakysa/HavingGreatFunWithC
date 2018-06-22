#include "network.h"

int responseToClient(SOCKET sockclt, SOCKADDR_IN *sin, char *buffer) {
    int result;
    if(result = sendto(sockclt, buffer, strlen(buffer), 0, (SOCKADDR *) sin, sizeof *sin)  == -1){
        printf("\ERREUR D'ENVOI DU PAQUET AU CLIENT : %d", result);
   }
   return result;
}

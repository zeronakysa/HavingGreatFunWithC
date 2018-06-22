#include "network.h"

#define SERVERPORT 2018
#define packetsize 15000


int main (int argc, char *argv[]) {
    WSADATA wsa;
    SOCKET sockServeur ;
    struct sockaddr_in server , client;



    printf("\nINITIALISATION DE WINSOCK");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0){  //WSAStartup(MAKEWORD(2, 2), &wsaData); //utilisation de la dll winsock
        printf("ERREUR DE DEMARRAGE DE WINSOCK : %d",WSAGetLastError());
        return 1;
    }

    printf("WINSOCK OK\n");

    //creation du socket
    if((sockServeur = socket(AF_INET , SOCK_DGRAM , 0 )) == INVALID_SOCKET){
        printf("Pb de creation du socket : %d" , WSAGetLastError());
    }
    printf("Socket cree.\n");

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( SERVERPORT );

    //liaison sin_adress et du port
    if( bind(sockServeur ,(struct sockaddr *)&server , sizeof(server)) == -1){
        printf("Erreur bind : %d" , WSAGetLastError());
    }

    printf("\nBind ok\n");

    char buffer [packetsize];
    while (1) {

        int clientlen = sizeof client;


        printf("\nEN ATTENTE D'UNE CONNEXION\n");

        if ( recvfrom(sockServeur, buffer, packetsize-1,0, ( SOCKADDR *)&client, &clientlen) ==-1){//Met l'IP et le port du client dans la structure client (sockaddr_in)
                //printf("\nPROBLEME DE RECEPTION");
        }//!  ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == -1)
        printf("\nDES DONNEES ONT ETE RECUES DE :");
        printf("\nIP CLIENT: %s", inet_ntoa(client.sin_addr));
        printf("\nPORT CLIENT: %d\n", (int) ntohs(client.sin_port));


        //Caractère de fin de chaine sur le buffer (pour printf)
        buffer[packetsize] = '\0';

        int sendToClient;
        client.sin_family = AF_INET; //IP du client = IPv4

        //Renvoi du paquet au client
        sendToClient = sendto(sockServeur, buffer, strlen(buffer), 0, (struct sockaddr *)&client, clientlen);
        if( sendToClient == -1){
           printf("ERREUR D'ENVOI: %d", sendToClient);
        }
        else {
            printf("\nLES DONNEES ONT ETE RENVOYEES");
            //printf("\nIP CLIENT: %s", inet_ntoa(client.sin_addr));
            //printf("\nPORT CLIENT: %d\n", (int) ntohs(client.sin_port));
        }
    }
    //Fermeture du socket et fin d'utilisation de winsock
    closesocket(sockServeur);
    WSACleanup();
return 0;
}

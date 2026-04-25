#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>

#include "utils.h"
#include "projet_config.h"


int initSocketClient(char* serverIp, int serverPort){
    int socketFd = ssocket();

    sconnect(serverIp, serverPort, socketFd);

    return socketFd;
}

int main(void){
    int socketfd = initSocketClient(SERVER_IP, SERVER_PORT);
    printf("Entrez des commandes : \n");

    pid_t forkID = sfork();
    while(1){
       
        char commande[MAX_COMMANDE]; 
        if(forkID != 0){ //parent
            int readInt = sread(0, commande, MAX_COMMANDE);
            if(readInt == 0){
                break;
            }
            swrite(socketfd, commande, readInt);
        }else{//fils
            int n = sread(socketfd, commande, MAX_COMMANDE -1);
            commande[n] = '\0';
            printf("Reasultat de la commande : %s\n", commande);
        }
    }
    int response = shutdown(socketfd, SHUT_RDWR);
    
    if(response == 0){
        sclose(socketfd); 
    }else{
       int status;
       waitpid(forkID, &status, 0);
    }
   
}
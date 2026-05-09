#include "utils.h"
#include "projet_config.h"
#include "string.h"
#include <unistd.h>

void start_zombie(void* arg){
    sexecl("./server", "zombie", (char*) arg, NULL);
}

void start_client(void* arg){
    sexecl("./client", "client", (char*) arg, NULL);
}

int main(int argc, char** argv){
    char port[16];
    sprintf(port, "%d", SERVER_PORT); 
    if(argc == 2){
        strcpy(port, argv[1]);
    }   

    printf("Démarrage du labo sur le port %s...\n", port);
    // démarrage zombie
    int zombiePid = fork_and_run1(start_zombie, port);
    sleep(1);
    // démarrage controleur
    int controllerPid = fork_and_run1(start_client, port);

    swaitpid(controllerPid, NULL, 0);
    skill(zombiePid, SIGTERM);
    swaitpid(zombiePid, NULL, 0);
}
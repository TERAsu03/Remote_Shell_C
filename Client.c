#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 256

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverSocket, clientSocket;

    //Création du socket client
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("Erreur lors de la création du socket");
        exit(1);
    }

    // Configuration de l'adresse du serveur
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(1234); //Numéro de port
    if (inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr) < 0) {
        perror("Erreur lors de la configuration de l'adresse du serveur");
        exit(1);
    }
    

}
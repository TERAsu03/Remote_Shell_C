#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 4096

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <serveur_ip> <serveur_port>\n", argv[0]);
        exit(1);
    }
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddress, clientAddress;

    //Création du socket client
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("Erreur lors de la création du socket");
        exit(1);
    }

    // Configuration de l'adresse du serveur
// Configuration de l'adresse du serveur
    serverAddress.sin_family = AF_INET;
    int port = atoi(argv[2]);
    serverAddress.sin_port = htons(port); // Numéro de port
    serverAddress.sin_addr.s_addr = inet_addr(argv[1]); // Utilisation de la variable server_ip



    
    //Connexion au serveur
    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        perror("Erreur lors de la connexion au serveur");
        exit(1);
    }

    //Boucle de communication du client
    char command[MAX_COMMAND_LENGTH];
    while (1) {
        printf("Entrez une commande : ");
        fgets(command, MAX_COMMAND_LENGTH, stdin);
        //Suppression le saut a la ligne de la commande
        command[strcspn(command, "\n")] = 0; 
        //Envoi de la commande au serveur
        if (send(clientSocket, command, strlen(command), 0) < 0) {
            perror("Erreur lors de l'envoi de la commande");
            break;
        }
        
        //Réception de la réponse du serveur
        sleep(1);
        char output[MAX_COMMAND_LENGTH];
        memset(output, 0, sizeof(output));
        int bytesReceived = recv(clientSocket, output, sizeof(output) -1, 0);
        if (bytesReceived == -1 ) {
            perror("Erreur lors de la réception de la réponse");
            break;
        } else if (bytesReceived == 0) {
            printf("Déconnexion du serveur\n");
            break;
        } else {
            printf("Réponse du serveur : %s\n", output);
        }   
    }

    //Fermeture du socket
    close(clientSocket);
    return 0;
}

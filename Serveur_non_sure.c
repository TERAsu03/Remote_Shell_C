#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 4096

int main(int arc, char *argv[]) {
   if (arc != 3) {
      printf("Usage: %s <server_ip><serveur_port\n", argv[0]);
      return(1);
   }
   int serverSocket, clientSocket;
   struct sockaddr_in serverAddress, clientAddress;
   socklen_t clientLength;

   //Création du socket
   serverSocket = socket(AF_INET, SOCK_STREAM, 0);
   if (serverSocket == -1) {
      perror("Erreur lors de la création du socket");
      exit(1);
   }
   
   // Configuration de l'adresse du serveur
   serverAddress.sin_family = AF_INET;
    int port = atoi(argv[2]);
   serverAddress.sin_port = htons(port); //Numéro de port
   serverAddress.sin_addr.s_addr = inet_addr(argv[1]); // Adresse IP spécifique
   
   // Effectuer la liaison du socket du serveur avec une adresse IP et un port spécifiques
   if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
      perror("Erreur lors de la liaison du socket");
      exit(1);
   }

   
   //Mettre le socket en écoute
   if (listen(serverSocket, 3) < 0) {
      perror("Erreur lors de l'écoute");
      exit(1);
   }
   
   //Acceptation de la connexion
   if ((clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, (socklen_t*)&clientLength))<0) {
      perror("Erreur lors de l'acceptation de la connexion");
      exit(1);
   }


   //Boucle de communication du serveur
   while(1) {
      char command[MAX_COMMAND_LENGTH];
      memset(command, 0, sizeof(command));

      //Reception de la commande
      if (recv(clientSocket, command, sizeof(command), 0) <= 0) {
         perror("Erreur lors de la réception de la commande");
         exit(1);   
      }
      
      // Vérifier si le client demande la fermeture du serveur
        if (strcmp(command, "exit-server") == 0) {
            printf("Demande de fermeture du serveur\n");
            break;
        }

      //Exécution de la commande système
      FILE* fp = popen(command, "r");
      if (fp == NULL) {
         perror("Erreur lors de l'exécution de la commande");
         break;
      }

      //Lecture de la sortie de la commande
      char output[4096]; 
      memset(output, 0, sizeof(output));
      while (fgets(output, sizeof(output), fp) != NULL) {
         //Envoi de la sortie de la commande
         if (send(clientSocket, output, strlen(output), 0) == -1) {
            perror("Erreur lors de l'envoi de la sortie de la commande");
            break;
         }
         memset(output, 0, sizeof(output));

         
         //Ajout du caractère de terminaison
         char terminationChar = '\0';
         if (send(clientSocket, &terminationChar, 1, 0) == -1) {
            perror("Erreur lors de l'envoi du caractère de terminaison");
            break;
         }
      }
      //Envoi du resultat de la commande
      if (send(clientSocket, "Fin de la commande", 19, 0) == -1) {
         perror("Erreur lors de l'envoi du résultat de la commande");
         break;
      }

      //Terminer la commande
      pclose(fp);
   }
}

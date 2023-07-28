#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 256

int main(int arc, char *argv[]) {
   
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
   serverAddress.sin_port = htons(1234); //Numéro de port
   
   //Liaison du socket avec l'adresse du serveur
   if (inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr) < 0) {
      perror("Erreur lors de la configuration de l'adresse du serveur");
      exit(1);
   }

   
   //Mettre le socket en écoute
   if (listen(serverSocket, 3) < 0) {
      perror("Erreur lors de l'écoute");
      exit(1);
   }
   
   //Acceptation de la connexion
   if ((clientSocket = accept(server_fd, (struct sockaddr *)&clientAddress, (socklen_t*)&clientLength))<0) {
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

      //Exécution de la commande système
      FILE* fp = popen(command, "r");
      if (fp == NULL) {
         perror("Erreur lors de l'exécution de la commande");
         break;
      }

      //Lecture de la sortie de la commande
      char output[256]; 
      memset(output, 0, sizeof(output));
      while (fgets(output, sizeof(output), fp) != NULL) {
         //Envoi de la sortie de la commande
         if (send(new_socket, output, strlen(output), 0) == -1) {
            perror("Erreur lors de l'envoi de la sortie de la commande");
            break;
         }
         memset(output, 0, sizeof(output));
      }
      //Envoi du resultat de la commande
      if (send(new_socket, "Fin de la commande", 19, 0) == -1) {
         perror("Erreur lors de l'envoi du résultat de la commande");
         break;
      }

      //Terminer la commande
      pclose(fp);
   }
# Remote Shell via sockets

## ⚠️Avertissement⚠️

Ce projet a été créé dans un but strictement pédagogique et démonstratif. L'application de contrôle à distance développée ici a pour objectif d'illustrer les concepts de base de la programmation c et de l'utilisation des sockets. Elle n'est pas destinée à être utilisée à des fins malveillantes ni à porter atteinte à la sécurité des systèmes. L'auteur ne prend aucune responsabilité pour toute utilisation abusive ou non autorisée de ce projet. Il est fortement recommandé de respecter les lois et les réglementations en vigueur lors de l'utilisation de toute application de ce type.

## Description:
Ce projet a été réalisé dans le cadre du cours de développement de l'option sécurité informatique (IR) de la deuxième année. L'objectif était de créer un programme de contrôle à distance utilisant des sockets pour échanger des commandes système entre un client et un serveur. Le projet démontre les compétences acquises en programmation c et en utilisation des sockets pour établir une communication bidirectionnelle entre deux machines. Le client envoie des commandes au serveur, qui les exécute et renvoie les résultats au client.

## Compilation
Client:
<pre>
  gcc -o Client Client.c
</pre>
Serveur:
<pre>
  gcc -o Serveur Serveur.c
</pre>
## Utilisation:
1 Compilation du code en utilisant les codes ci-dessus 

2 Exécuter le serveur

<pre>
  ./Serveur "adresse_ip" "numero_port"
</pre>
3 Exécuter le client 
<pre>
  ./Client "adresse_ip" "numero_port"
</pre>
4 Entrer le code dans le prompt du client
Exemple
<pre>
  Entrez une commande : whoami
</pre>
## Notes:
Assurez-vous que le client et le serveur sont exécutés sur des machines accessibles via le réseau.
Pour terminer le code utiliser la commande exit dans le prompt du client
<pre>
  Entrer une commande : exit
  Demande de fermeture du serveur
  Deconnexion du client
</pre>
## Auteur
Thomas Vanderhoeven
## License
Ce projet est sous license


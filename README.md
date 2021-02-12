# Projet-OS

Dans ce projet le but est de créer un mini shell en c ou tout autre langage

1RE partie:

- Le shell est en premier lieu géré par le buffer qui va ensuite demander la commande à faire: grâce à un fgets

- la suite du code permet de prendre en compte les caractères espaces pour permettre les options comme "ls -la" par exemple

- une condition est crée avec la fonction glob qui recherche tous les chemins d'accès correspondant au motif pattern en utilisant les règles du shell

2EME partie:

- un fork est employé et crée donc un processus fils puis on gère le processus père avec une fonction
	si le processus père = 0 on se met dans le processus fils qui remplace le processus actuel par le contenu des paramètres passés et exécute celui-ci
	sinon process != 0 on se met en attente de la fin du processus fils grâce à la commande wait

- à la fin de toutes les boucles on libère la mémoire de lisstes d'arguments et du pointeur p qui gère le buffer


Le shell s'utilise simplement dans le dossie actuelle, celui-ci peut uniquement exécuter des commandes qui agissent sur le dossier en cours, dont "nano", "mkdir", "touch" la commande cd en revanche ne fonctionne pas 


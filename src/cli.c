/************************************************************************************/
/********************************** Bibliothèques ***********************************/
/************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "common.h"
#include "cli.h"
#include "btree.h"
#include "query.h"


/************************************************************************************/
/************************************* Fonctions ************************************/
/************************************************************************************/
/**************************/
/***** Interface CLI  *****/
/**************************/
void executeCLI() {
	/***** Variables *****/
	char userInput[200]; // Chaîne contenant la saisi utilisateur.
	stc_node *liste_personnes = NULL; // Création du noeud racine / de la table liste_personnes.
	
	/***** Fonctions *****/
	clearScreen(); // Effacer la console.
	printf("Use '?' to display available commands.\n\n"); // Afficher le message d'aide.
	
	while (1) { // Boucle infini.
	printf("binaryTree > "); // Prompt.
		readString(userInput, 200); // Récupérer la saisi utilisateur.
		
		if (strcmp(userInput, "?") == 0) { // Afficher les commandes disponibles.
			printf("\n?		Display available commands.\n");
			printf("clear		Clear the console.\n");
			printf("SELECT		Display existing row.		FORMAT : SELECT column1 column2 column3		FORMAT : SELECT *\n");
			printf("INSERT		Insert a new row.		FORMAT : INSERT value1 value2\n");
			printf("DELETE		Remove existing row.		FORMAT : DELETE WHERE column1='value'		FORMAT : DELETE *\n");
			printf("quit		Exit the program.\n\n");
		}
		
		if (strcmp(userInput, "quit") == 0) { // Quitter
			freeTree(liste_personnes); // Libérer la mémoire allouer pour l'arbre.
			exit(EXIT_SUCCESS);
		}
		if (strcmp(userInput, "clear") == 0) { // Effacer la console.
			clearScreen();
		}
		if (strstr(userInput, "SELECT") != NULL) { // Faire un SELECT.
			int argNb = findCharNumberInString(userInput, ' '); // Récupérer le nombre d'espace dans la requête.
			if(argNb < 1 || argNb > 3) { // Informer le format de la requête SI l'utilisateur ne fournis pas le bon nombre d'argument.
				printf("FORMAT :	SELECT colonnes\n\n");
			}
			else {
				selectRow(userInput, liste_personnes);
			}
		}
		if (strstr(userInput, "INSERT") != NULL) { // Faire un INSERT.
			int argNb = findCharNumberInString(userInput, ' '); // Récupérer le nombre d'espace dans la requête.
			if(argNb != 2) { // Informer le format de la requête si l'utilisateur ne fournis pas le bon nombre d'argument.
				printf("FORMAT :	INSERT prenom nom\n\n");
			}
			else {
				liste_personnes = insertNewRow(userInput, liste_personnes);
			}
		}
		if (strstr(userInput, "DELETE") != NULL) { // Faire un DELETE.
			int argNb = findCharNumberInString(userInput, ' '); // Récupérer le nombre d'espace dans la requête.
			if(argNb < 1 || argNb > 2) { // Informer le format de la requête si l'utilisateur ne fournis pas le bon nombre d'argument.
				printf("DELETE WHERE column1='value'\n\n");
			}
			else {
				liste_personnes = deleteRow(userInput, liste_personnes);
			}
		}
	}
}

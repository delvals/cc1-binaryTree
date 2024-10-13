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
	
	while (1 == 1) { // Boucle infini.
	printf("binaryTree > "); // Prompt.
		readString(userInput, 200); // Récupérer la saisi utilisateur.
		
		if (strcmp(userInput, "?") == 0) { // Afficher les commandes disponibles.
			printf("\n?		Display available commands.\n");
			printf("clear		Clear the console.\n");
			printf("SELECT		Display existing row.		NOT WORKING YET.\n");
			printf("INSERT		Insert a new row.		FORMAT : INSERT prenom nom\n");
			printf("quit		Exit the program.\n\n");
		}
		
		if (strcmp(userInput, "quit") == 0) { // Quitter
			freeTree(liste_personnes); // Libérer la mémoire allouer pour l'arbre.
			exit(EXIT_SUCCESS);
		}
		if (strcmp(userInput, "clear") == 0) { // Effacer la console.
			clearScreen();
		}
		if (strstr(userInput, "INSERT") != NULL) {
			int argNb = findCharNumberInString(userInput, ' '); // Récupérer le nombre d'espace dans la requête.
			if(argNb != 2) { // Informer le format de la requête si l'utilisateur ne fournis pas le bon nombre d'argument.
				printf("FORMAT :	INSERT prenom nom\n\n");
			}
			else {
				liste_personnes = insertNewRow(userInput, liste_personnes);
				
				////////////////////////////////////////// TESTS POUR LE DEV //////////////////////////////////////////////////////////////////////////////////////
				printf("\nStructure de l'arbre : ");
				preOrderPrint(liste_personnes);
				printf("\n\n");
				if (NULL != searchNodeViaPrimaryKey(liste_personnes, 1)) {
					stc_node *noeud = searchNodeViaPrimaryKey(liste_personnes, 1);
					printf("Insertion du noeud numero %d\n", noeud->primaryKey);
					printf("Insertion du prenom %s\n", noeud->row.first_name);
					printf("Insertion du nom %s\n\n", noeud->row.last_name);
				}
				if (NULL != searchNodeViaPrimaryKey(liste_personnes, 2)) {
					stc_node *noeud = searchNodeViaPrimaryKey(liste_personnes, 2);
					printf("Insertion du noeud numero %d\n", noeud->primaryKey);
					printf("Insertion du prenom %s\n", noeud->row.first_name);
					printf("Insertion du nom %s\n\n", noeud->row.last_name);
				}
			}
		}
	}
}

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
#include "avl.h"
#include "save.h"


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
	printf("\nDo you want to load data from file ? ");
	printf("\n\nType 'yes' or press Enter : ");
	readString(userInput, 200); // Récupérer la saisi utilisateur.
	if (strcmp(userInput, "yes") == 0) {
		printf("\n");
		liste_personnes = loadData(liste_personnes); // Charger les données.
	}
	
	printf("\nUse '?' to display available commands.\n\n"); // Afficher le message d'aide.
	
	while (1) { // Boucle infini.
		printf("binaryTree > "); // Prompt.
		readString(userInput, 200); // Récupérer la saisi utilisateur.
		
		if (strcmp(userInput, "?") == 0) { // Afficher les commandes disponibles.
			printf("\n?		Display available commands.\n");
			printf("clear		Clear the console.\n");
			printf("save		Save data to file.\n");
			printf("load		Load data from file.\n");
			printf("reset		Reset all data.\n");
			printf("show tree	Display the binary tree.\n");
			printf("quit		Exit the program.\n");
			printf("SELECT		Display existing row.		FORMAT : SELECT column1 column2 column3		FORMAT : SELECT *\n");
			printf("INSERT		Insert a new row.		FORMAT : INSERT value1 value2\n");
			printf("DELETE		Remove existing row.		FORMAT : DELETE WHERE column1='value'		FORMAT : DELETE *\n\n");
		}
		if (strcmp(userInput, "quit") == 0) { // Quitter
			printf("\nDo you want to save data to file ? ");
			printf("\n\nType 'yes' or press Enter : ");
			readString(userInput, 200); // Récupérer la saisi utilisateur.
			if (strcmp(userInput, "yes") == 0) {
				printf("\n");
				saveData(liste_personnes);
			}
			
			freeTree(liste_personnes); // Libérer la mémoire allouer pour l'arbre.
			exit(EXIT_SUCCESS);
		}
		if (strcmp(userInput, "clear") == 0) { // Effacer la console.
			clearScreen();
		}
		if (strstr(userInput, "SELECT") != NULL) { // Faire un SELECT.
			int argNb = findCharNumberInString(userInput, ' '); // Récupérer le nombre d'espace dans la requête.
			if(argNb < 1 || argNb > 3) { // Informer le format de la requête SI l'utilisateur ne fournis pas le bon nombre d'argument.
				printf("\nFORMAT :	SELECT colonnes\n\n");
			}
			else {
				selectRow(userInput, liste_personnes);
			}
		}
		if (strstr(userInput, "INSERT") != NULL) { // Faire un INSERT.
			int argNb = findCharNumberInString(userInput, ' '); // Récupérer le nombre d'espace dans la requête.
			if(argNb != 2) { // Informer le format de la requête si l'utilisateur ne fournis pas le bon nombre d'argument.
				printf("\nFORMAT :	INSERT prenom nom\n\n");
			}
			else {
				liste_personnes = insertNewRow(userInput, liste_personnes);
			}
		}
		if (strstr(userInput, "DELETE") != NULL) { // Faire un DELETE.
			int argNb = findCharNumberInString(userInput, ' '); // Récupérer le nombre d'espace dans la requête.
			if(argNb < 1 || argNb > 2) { // Informer le format de la requête si l'utilisateur ne fournis pas le bon nombre d'argument.
				printf("\nDELETE WHERE column1='value'\n\n");
			}
			else {
				liste_personnes = deleteRow(userInput, liste_personnes);
			}
		}
		if (strcmp(userInput, "show tree") == 0) { // Affiche l'arbre.
			printf("\n");
			preOrderPrint(liste_personnes);
			printf("\n\n");
		}
		if (strcmp(userInput, "save") == 0) { // Sauvegarder les données.
			printf("\n");
			saveData(liste_personnes);
			printf("\n\n");
		}
		if (strcmp(userInput, "reset") == 0) { // Sauvegarder les données.
			printf("\n");
			freeTree(liste_personnes); // Libérer la mémoire allouer pour l'arbre.
			liste_personnes = NULL; // Réassigner la racine.
			printf("\n\n");
		}
		if (strcmp(userInput, "load") == 0) { // Sauvegarder les données.
			printf("\n");
			freeTree(liste_personnes); // Libérer la mémoire allouer pour l'arbre.
			liste_personnes = NULL; // Réassigner la racine.
			liste_personnes = loadData(liste_personnes); // Charger les données.
			printf("\n\n");
		}
	}
}

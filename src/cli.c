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
/************************************ Prototypes ************************************/
/************************************************************************************/

void changePromptColor(char *userInput, char *color);

/************************************************************************************/
/************************************* Fonctions ************************************/
/************************************************************************************/

/**************************/
/***** Interface CLI  *****/
/**************************/
void executeCLI() {
	/***** Variables *****/
	char color[] = "\033[0;31m"; // Couleur du prompt, rouge par défaut.
	char userInput[200]; // Chaîne contenant la saisi utilisateur.
	stc_node *liste_personnes = NULL; // Création du noeud racine / de la table liste_personnes.
	
	/***** Fonctions *****/
	clearScreen(); // Effacer la console.
	printf("\nDo you want to load data from file ? ");
	printf("\n\nType 'yes' or press Enter : ");
	readString(userInput, 200); // Récupérer la saisi utilisateur.
	if (strcmp(userInput, "yes") == 0) {
		liste_personnes = loadData(liste_personnes); // Charger les données.
	}
	else {
		printf("\n");
	}
	
	printf("Use '?' to display available commands and table information.\n\n"); // Afficher le message d'aide.
	
	while (1) { // Boucle infini.
		printf("%s", color);
		printf("binaryTree > "); // Prompt.
		printf("\033[0m");
		readString(userInput, 200); // Récupérer la saisi utilisateur.
		
		if (strcmp(userInput, "?") == 0) { // Afficher les commandes disponibles.
			printf("\n?		Display available commands.\n");
			printf("clear		Clear the console.\n");
			printf("save		Save data to file.\n");
			printf("load		Load data from file.\n");
			printf("reset		Reset all data in RAM.\n");
			printf("showtree	Display the binary tree.			FORMAT : showtree <type>					TYPES : preorder, inorder, preorder\n");
			printf("color		Change color of prompt.				FORMAT : color <color>						COLORS : cyan, red, green\n");
			printf("quit		Exit the program.\n");
			printf("SELECT		Display specific column(s) of the table.	FORMAT : SELECT <column1> <column2> <column3>...		COLUMNS : *, primaryKey, first_name, last_name\n");
			printf("INSERT		Insert a new row.				FORMAT : INSERT <first_name> <last_name>\n");
			printf("DELETE WHERE	Remove existing row.				FORMAT : DELETE WHERE <column1> ='<value>'			FORMAT : DELETE *\n\n");
		}
		else if (strcmp(userInput, "quit") == 0) { // Quitter
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
		else if (strcmp(userInput, "clear") == 0) { // Effacer la console.
			clearScreen();
		}
		else if (strstr(userInput, "SELECT") != NULL) { // Faire un SELECT.
			int argNb = findCharNumberInString(userInput, ' '); // Récupérer le nombre d'espace dans la requête.
			if(argNb < 1 || argNb > 3) { // Informer le format de la requête SI l'utilisateur ne fournis pas le bon nombre d'argument.
				printf("\nFORMAT :	SELECT colonnes\n\n");
			}
			else {
				selectRow(userInput, liste_personnes);
			}
		}
		else if (strstr(userInput, "INSERT") != NULL) { // Faire un INSERT.
			liste_personnes = insertNewRow(userInput, liste_personnes);
		}
		else if (strstr(userInput, "DELETE") != NULL) { // Faire un DELETE.
			liste_personnes = deleteRow(userInput, liste_personnes);
		}
		else if (strstr(userInput, "showtree") != NULL) { // Affiche l'arbre.
			showTree(userInput, liste_personnes);
		}
		else if (strcmp(userInput, "save") == 0) { // Sauvegarder les données.
			saveData(liste_personnes);
		}
		else if (strcmp(userInput, "reset") == 0) { // Sauvegarder les données.
			printf("\n");
			freeTree(liste_personnes); // Libérer la mémoire allouer pour l'arbre.
			liste_personnes = NULL; // Réassigner la racine.
			printf("Data has been reset in RAM !\n\n");
			printf("Saving file is unchanged.\n\n");
		}
		else if (strcmp(userInput, "load") == 0) { // Sauvegarder les données.
			freeTree(liste_personnes); // Libérer la mémoire allouer pour l'arbre.
			liste_personnes = NULL; // Réassigner la racine.
			liste_personnes = loadData(liste_personnes); // Charger les données.
		}
		else if (strstr(userInput, "color") != NULL) { // Changer la couleur du prompt.
			changePromptColor(userInput, color);
		}
		else {
			printf("\nUnknown command.\n\n");
		}
	}
}

void changePromptColor(char *userInput, char *color) {
	int argNb = findCharNumberInString(userInput, ' '); // Récupérer le nombre d'espace dans la requête.
	if(argNb == 1) { // Informer le format de la requête SI l'utilisateur ne fournis pas le bon nombre d'argument.
		if (strcmp(userInput, "color cyan") == 0) {
			replaceStringBy(color, "\033[0;36m");
			printf("\nColor changed to cyan !\n\n");
		}
		else if (strcmp(userInput, "color red") == 0) {
			replaceStringBy(color, "\033[0;31m");
			printf("\nColor changed to red !\n\n");
		}
		else if (strcmp(userInput, "color green") == 0) {
			replaceStringBy(color, "\033[0;32m");
			printf("\nColor changed to green !\n\n");
		}
		else {
			printf("\nColor is not recognized !\n");
			printf("\nCOLORS : cyan, red, green\n\n");
		}
	}
	else {
		printf("\nFormat is not correct !\n");
		printf("\nFORMAT : color <color>\n\n");
	}
}

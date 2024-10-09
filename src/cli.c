/************************************************************************************/
/********************************** Bibliothèques ***********************************/
/************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "func-common.h"
#include "cli.h"
#include "btree.h"
#include "save.h"

/************************************************************************************/
/************************************* Fonctions ************************************/
/************************************************************************************/

void executeCLI() {
	char userInput[200]; // Chaîne contenant la saisi utilisateur.
	
	clearScreen(); // Effacer la console.
	printf("Use '?' to display available commands.\n\n"); // Afficher le message d'aide.
	
	while (1 == 1) { // Boucle infini.
	printf("binaryTree > "); // Prompt.
		readString(userInput, 200); // Récupérer la saisi utilisateur.
		
		if (strcmp(userInput, "?") == 0) { // Afficher les commandes disponibles.
			printf("\n?	Display available commands.\n");
			printf("clear	Clear the console.\n");
			printf("quit	Exit the program.\n\n");
		}
		
		if (strcmp(userInput, "quit") == 0) { // Quitter
			exit(EXIT_SUCCESS);
		}
		
		if (strcmp(userInput, "clear") == 0) { // Effacer la console.
			clearScreen();
		}
	}
}

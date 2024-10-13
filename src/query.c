/************************************************************************************/
/********************************** Bibliothèques ***********************************/
/************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "btree.h"
#include "query.h"


/************************************************************************************/
/************************************* Fonctions ************************************/
/************************************************************************************/

/*******************************************/
/***** Insérer une nouvelle ligne SQL  *****/
/*******************************************/
stc_node *insertNewRow(char *userInput, stc_node *liste_personnes) {
	/***** Variables *****/
	int position = 0;
	uint8_t spaceNb = 0, last_name_position = 0, first_name_position = 0;
	char last_name[50] = "";
	char first_name[50] = "";
	/***** Fonctions *****/
	for (position = 0; position < strlen(userInput); position++) { // On parcourt les caractères dans la saisi utilisateur.
		if (userInput[position] == ' ') { // Lorsqu'il y a un ESPACE, on incrémente le compteur.
			spaceNb += 1;
		}
		if (userInput[position] != ' ' && spaceNb == 1) { // La première valeur (prénom) se trouve après le premier ESPACE.
			first_name[first_name_position] = userInput[position]; // On récupère la valeur dans une variable.
			first_name_position += 1;
		}
		if (userInput[position] != ' ' && spaceNb == 2) { // La deuxième valeur (nom) se trouve après le deuxième ESPACE.
			last_name[last_name_position] = userInput[position]; // On récupère la valeur dans une variable.
			last_name_position += 1;
		}
	}
	liste_personnes = insertNode(liste_personnes, first_name, last_name); // Insérer la ligne SQL dans l'arbre.
	return liste_personnes;
}

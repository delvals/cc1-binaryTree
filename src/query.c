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

/********************************/
/***** Afficher lignes SQL  *****/
/********************************/
void selectRow(char *userInput, stc_node *liste_personnes) {
	/***** Variables *****/
	int tableSize = countNodes(liste_personnes);
	int nodeCounter = 0;
	bool argumentAll = false;
	bool argumentPrimaryKey = false;
	bool argument_first_name = false;
	bool argument_last_name = false;
	/***** Analyse de la requète SQL et afficher l'en-tête *****/
	if (strstr(userInput, "*") != NULL) { // SI l'utilisateur à choisi d'afficher toutes les collones...
		argumentAll = true; // Rendre vrai le boolean qui affichera les résultats.
		printf("\n");
		printf("	primaryKey	|	first_name	|	last_name	\n\n"); // Afficher les en-têtes.
	}
	else { // SINON, afficher le/les colonne(s) selon les choix de l'utilisateur.
		printf("\n");
		if (strstr(userInput, "primaryKey") != NULL) {
			argumentPrimaryKey = true; // Rendre vrai le boolean qui affichera les résultats.
			printf("	primaryKey	|"); // Afficher l'en-tête.
		}
		if (strstr(userInput, "first_name") != NULL) {
			argument_first_name = true; // Rendre vrai le boolean qui affichera les résultats.
			printf("	first_name	|"); // Afficher l'en-tête.
		}
		if (strstr(userInput, "last_name") != NULL) {
			argument_last_name = true; // Rendre vrai le boolean qui affichera les résultats.
			printf("	last_name	"); // Afficher l'en-tête.
		} 
		printf("\n\n");
	}
	/***** Afficher les résultats *****/
	if (tableSize != 0) { // On verifie qu'il y a au moins une ligne SQL.
		for (nodeCounter = 1; nodeCounter <= tableSize; nodeCounter++) { // On parcourt les noeuds de l'arbre.
			stc_node *currentNode = searchNodeViaPrimaryKey(liste_personnes, nodeCounter); // On récupère l'adresse du noeud en cours.
			if (NULL != currentNode) { // SI le noeud existe...
				if (argumentAll == true) { //...SI l'utilisateur à choisi d'afficher toutes les collones...
					argumentAll = true;
					printf("	%d		|	%s		|	%s		", currentNode->primaryKey, currentNode->row.first_name, currentNode->row.last_name);
				}
				else { //...SINON, afficher le/les colonne(s) selon les choix de l'utilisateur.
					if (argumentPrimaryKey == true) {
						printf("	%d		|", currentNode->primaryKey);
					}
					if (argument_first_name == true) {
						printf("	%s		|", currentNode->row.first_name);
					}
					if (argument_last_name == true) {
						printf("	%s		", currentNode->row.last_name);
					}
				}
				printf("\n");
			}
		}
	}
	printf("\n%d row(s) in set\n", tableSize);
	printf("\n");
}

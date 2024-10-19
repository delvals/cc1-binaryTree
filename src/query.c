/************************************************************************************/
/********************************** Bibliothèques ***********************************/
/************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
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
	printf("Query OK, 1 row affected.\n\n");
	return liste_personnes;
}

/********************************/
/***** Afficher lignes SQL  *****/
/********************************/
void selectRow(char *userInput, stc_node *liste_personnes) {
	/***** Variables *****/
	int nodeCounter = 0, rowSelectedNb = 0, tableSize = countNodes(liste_personnes);
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
		int maxPrimaryKey = findNodeMaxPrimaryKey(liste_personnes)->primaryKey; // On récupère la clé primaire maximum.
		for (nodeCounter = 1; nodeCounter <= maxPrimaryKey; nodeCounter++) { // On parcourt les noeuds de l'arbre.
			stc_node *currentNode = searchNodeViaPrimaryKey(liste_personnes, nodeCounter); // On récupère l'adresse du noeud en cours.
			if (NULL != currentNode) { // SI le noeud existe...
				rowSelectedNb++;
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
	printf("\n%d row(s) in set\n", rowSelectedNb); // FAUT FAIRE UN COMPTEUR
	printf("\n");
}

/********************************/
/***** Supprimer lignes SQL  ****/
/********************************/
stc_node *deleteRow(char *userInput, stc_node *liste_personnes) {
	/***** Variables *****/
	int tableSize = countNodes(liste_personnes);
	int nodeCounter = 1, position = 0, rowDeletedNb = 0, conditionPosition = 0, primaryKey = 0;
	uint8_t singleQuoteNb = 0;
	char condition[50] = "";
	bool argumentAll = false;
	bool argumentPrimaryKey = false;
	bool argument_first_name = false;
	bool argument_last_name = false;
	/***** Fonctions *****/
	if (tableSize != 0) { // On verifie qu'il y a au moins une ligne SQL.
		/* Analyse de la condition */
		if (strstr(userInput, "*") != NULL) { // SI l'utilisateur veut supprimer toutes les données...
			argumentAll = true;
		}
		else if ((strstr(userInput, "WHERE") != NULL) && (strstr(userInput, "primaryKey") != NULL)) { // SI l'utilisateur veut supprimer selon la valeur d'une clé primaire...
			argumentPrimaryKey = true;
		}
		else if ((strstr(userInput, "WHERE") != NULL) && (strstr(userInput, "first_name") != NULL)) { // SI l'utilisateur veut supprimer selon la valeur d'un prénom...
			argument_first_name = true;
		}
		else if ((strstr(userInput, "WHERE") != NULL) && (strstr(userInput, "last_name") != NULL)) { // SI l'utilisateur veut supprimer selon la valeur d'un nom...
			argument_last_name = true;
		}
		else {
			printf("Query OK, 0 row affected.\n\n");
			return liste_personnes;
		}
		
		/* Récupération de la condition */
		for (position = 0; position < strlen(userInput); position++) { // On parcourt les caractères dans la saisi utilisateur.
			if (singleQuoteNb == 1) { // La valeur à récupéré se trouve entre deux guillements simples.
				condition[conditionPosition] = userInput[position]; // On récupère la valeur dans une variable.
				conditionPosition += 1;
			}
			if (userInput[position] == '\'') { // Lorsqu'il y a un guillement simple, on incrémente le compteur.
				singleQuoteNb += 1;
			}
		}
		condition[strlen(condition) - 1] = '\0'; // Supression du deuxième guillement simple.
		
		/* Conversion */
		if (true == argumentPrimaryKey) { // SI l'utilisateur veut supprimer selon la valeur d'une clé primaire...
			primaryKey = atoi(condition); // ...on convertit en entier la condition.
		}
		
		/* Supression */
		if ((true == argumentPrimaryKey) && (NULL != searchNodeViaPrimaryKey(liste_personnes, primaryKey))) {
			liste_personnes = deleteNode(liste_personnes, primaryKey);
			printf("Query OK, 1 row affected.\n\n");
			return liste_personnes;
		}
		for (nodeCounter = 1; nodeCounter <= tableSize; nodeCounter++) { // On parcourt les noeuds de l'arbre.
			stc_node *currentNode = searchNodeViaPrimaryKey(liste_personnes, nodeCounter); // On récupère l'adresse du noeud en cours.
			if (NULL != currentNode) { // SI le noeud existe...
				if (argumentAll == true) { // SI l'utilisateur veut supprimer selon la valeur d'un prénom et la condition est remplie...
					liste_personnes = deleteNode(liste_personnes, nodeCounter); //...supprimer le noeud actuel.
					rowDeletedNb++; //...le compteur de lignes supprimées s'incrémente.
				}
				else if ((argument_first_name == true) && (strcmp(currentNode->row.first_name,condition) == 0)) { // SI l'utilisateur veut supprimer selon la valeur d'un prénom et la condition est remplie...
					liste_personnes = deleteNode(liste_personnes, nodeCounter); //...supprimer le noeud actuel.
					rowDeletedNb++; //...le compteur de lignes supprimées s'incrémente.
				}
				else if ((argument_last_name == true) && (strcmp(currentNode->row.last_name,condition) == 0)) { // SI l'utilisateur veut supprimer selon la valeur d'un prénom et la condition est remplie...
					liste_personnes = deleteNode(liste_personnes, nodeCounter); //...supprimer le noeud actuel.
					rowDeletedNb++; //...le compteur de lignes supprimées s'incrémente.
				}
			}
		}
		printf("Query OK, %d row(s) affected.\n\n", rowDeletedNb);
		return liste_personnes;
	}
	else {
		printf("Table is empty.\n");
		printf("Query OK, 0 row affected.\n\n");
	}
	return liste_personnes;
}

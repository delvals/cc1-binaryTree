/************************************************************************************/
/********************************** Bibliothèques ***********************************/
/************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "common.h"
#include "save.h"
#include "btree.h"

/************************************************************************************/
/************************************* Fonctions ************************************/
/************************************************************************************/

/*******************************/
/***** Charger les données *****/
/*******************************/
stc_node *loadData(stc_node *liste_personnes) {
	/* Variables */
	liste_personnes = NULL;
	int primaryKey = 0;
	char first_name[50], last_name[50];
	
	/* Fonctions */
	printf("\n");
    	FILE *saveFile = fopen("../save/save.txt", "r"); // Ouverture du fichier en lecture seule.
    	if(NULL == saveFile) { // SI l'ouverture du fichier à échouée...
    		printf("The saving file could not be opened or does not exist !\n\n");
    		return liste_personnes;
    	}
    	else { // SINON, SI l'ouverture du fichier à réussi...
    		while(fscanf(saveFile, "%d %s %s", &primaryKey, &first_name, &last_name) == 3) { // On récupère chaque argument, de chaque ligne du fichier, tant qu'il y a 3 arguments dans la ligne.
  			/* Récupérer les données à sauvegarder */
			liste_personnes = insertNodeHelper(liste_personnes, primaryKey, first_name, last_name);
    		}
    		printf("Data loaded !\n\n");
    	}
	fclose(saveFile); // Fermeture du fichier de sauvegarde.
	return liste_personnes;
}

/***********************************/
/***** Sauvegarder les données *****/
/***********************************/
void saveData(stc_node *liste_personnes) {
    	/* Variables */
	int nodeCounter = 0, tableSize = countNodes(liste_personnes);
	if (0 != tableSize) { // SI la table n'est pas vide...
		/* Fichier */
	    	FILE *saveFile = fopen("../save/save.txt", "w+"); // Ouverture du fichier de sauvegarde en écriture avec supression des données existantes.
	    	if(NULL == saveFile) { // SI l'ouverture du fichier à échouée...
	    		printf("The saving file could not be opened !\n");
	    	}
	    	else { // SINON, SI l'ouverture du fichier à réussi...
	    		int maxPrimaryKey = findNodeMaxPrimaryKey(liste_personnes)->primaryKey; // On récupère la clé primaire maximum.
	    		for (nodeCounter = 1; nodeCounter <= maxPrimaryKey; nodeCounter++) { // On parcourt les noeuds de l'arbre.
	    			/* Récupérer les données à sauvegarder */
				stc_node *currentNode = searchNodeViaPrimaryKey(liste_personnes, nodeCounter); // On récupère l'adresse du noeud en cours.
				if (NULL != currentNode) { // SI le noeud existe...
					/* Ecrire les données dans le fichier de sauvegarde */
					fprintf(saveFile, "%d %s %s\n", currentNode->primaryKey, currentNode->row.first_name, currentNode->row.last_name);
				}
			}
	    	}
		fclose(saveFile); // Fermeture du fichier de sauvegarde.
		printf("Data saved !");
	}
	else { // SINON, SI la table est vide...
		printf("Table is empty !");
	}
}

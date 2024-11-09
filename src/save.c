/************************************************************************************/
/********************************** Bibliothèques ***********************************/
/************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include "include/common.h"
#include "include/save.h"
#include "include/btree.h"

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
    	FILE *saveFile = fopen("save/save.txt", "r"); // Ouverture du fichier en lecture seule.
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
		/* Fonctions */
		printf("\n");
	    	FILE *saveFile = fopen("save/save.txt", "w+"); // Ouverture du fichier de sauvegarde en écriture avec supression des données existantes.
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
			fclose(saveFile); // Fermeture du fichier de sauvegarde.
			printf("Data saved !");
	    	}
	}
	else { // SINON, SI la table est vide...
		printf("\nTable is empty !");
		printf("\n\nDo you want to reset the save file ? ");
		printf("\n\nType 'yes' or press Enter : ");
		char userInput[200];
		readString(userInput, 200); // Récupérer la saisi utilisateur.
		if (strcmp(userInput, "yes") == 0) {
		    	FILE *saveFile = fopen("save/save.txt", "w+"); // Ouverture du fichier de sauvegarde en écriture avec supression des données existantes.
		    	if(NULL == saveFile) { // SI l'ouverture du fichier à échouée...
		    		printf("The saving file could not be opened !\n");
		    	}
		    	else { // SINON, SI l'ouverture du fichier à réussi...
		    		fprintf(saveFile, "");
		    	}
		}
	}
	printf("\n");
}

/****************************************/
/* Création du répertoire de sauvegarde */
/****************************************/
void createSaveDirectory() {
	DIR* dir = opendir("save");
	if (dir) { // SI le répertoire existe déjà...
		FILE *saveFile = fopen("save/save.txt", "r"); // Ouverture du fichier en lecture seule.
	    	if(NULL == saveFile) { // SI l'ouverture du fichier à échouée...
	    		FILE *saveFileToCreate;
			saveFileToCreate = fopen("save/save.txt", "w"); //...créer le fichier.
			fclose(saveFileToCreate);
	    	}
	    	fclose(saveFile);
	    	closedir(dir); //...fermer le répertoire.
	}
	else if (ENOENT == errno) { // SINON, SI le répertoire n'éxiste pas...
		mkdir("save", 0700);
		FILE *saveFileToCreate;
		saveFileToCreate = fopen("save/save.txt", "w"); //...créer le fichier.
		fclose(saveFileToCreate);
	}
	else { // SI la fonction échoue...
    		printf("Function createDirectory failed !");
		exit(EXIT_FAILURE);
	}
 }

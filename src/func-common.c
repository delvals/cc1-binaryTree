/************************************************************************************/
/***************** Constante de préprocesseur système d'exploitation ****************/
/************************************************************************************/

#ifdef _WIN32 // Si, l'OS est Windows.
    #define __OS__ 'w'
    
#elif defined(__linux__) // Sinon si, l'OS est Linux.
    #define __OS__ 'l'

#elif defined(__APPLE__) // Sinon si, l'OS est MACOS.
    #define __OS__ 'm'

#else // Sinon si, l'OS n'est pas reconnu.
    #define __OS__ 'n'
#endif

/************************************************************************************/
/********************************** Bibliothèques ***********************************/
/************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "func-common.h"
#include "btree.h"
#include "save.h"

/************************************************************************************/
/************************************* Fonctions ************************************/
/************************************************************************************/
 
/***********************************/
/***** Vider le buffer clavier *****/
/***********************************/
void emptyBuffer()
{
    int c = 0;
    /* On boucle tant qu'on n'a pas récupéré le caractère \n et le symbole EOF(fin de fichier),
       qui signifient tous deux "vous êtes arrivé à la fin du buffer". */
    while (c != '\n' && c != EOF)
    {
        c = getchar(); // On récupère le contenu du buffer afin de la vider.
    }
}

/****************************/
/***** Nettoyer l'écran *****/
/****************************/
void clearScreen() {
	if (__OS__ == 'w') { // Si le programme est compilé sur Windows,
		system ("cls");
	}
	else if (__OS__ == 'l') { // Si le programme est compilé sur Linux,
		system ("clear");
	}
	else if (__OS__ == 'm') { // Si le programme est compilé sur MACOS,
		system ("clear");
	}
	else if (__OS__ == 'n') { // Si le programme est compilé sur un système non reconnu,
		printf("\e[1;1H\e[2J");
	}
}

/******************************************/
/***** Récupérer la saisi utilisateur *****/
/******************************************/
void readString(char *chaine, int longueur)
{
    char *positionEntree = NULL; // Initialisation du pointeur
 
    if (fgets(chaine, longueur, stdin) != NULL)  //  Si la saisi clavier "stdin" ne retourne pas d'erreur,
    {
        positionEntree = strchr(chaine, '\n'); // On recherche l'adresse contenant "\n" produit par l'appui sur "Entrée".
        if (positionEntree != NULL) // Si le resultat de la recherche n'est pas NULL mais l'adresse
        {
            *positionEntree = '\0'; // On remplace "\n" par "\0", soit la fin de chaîne.
        }
        else
        {
            emptyBuffer();
        }
    }
    else
    {
        emptyBuffer();
    }
}
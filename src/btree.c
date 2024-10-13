/************************************************************************************/
/********************************** Bibliothèques ***********************************/
/************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "btree.h"

/************************************************************************************/
/************************************* Fonctions ************************************/
/************************************************************************************/

/******************************************/
/* Chercher un noeud via sa clé primaire */
/******************************************/
stc_node *searchNodeViaPrimaryKey(stc_node *root, int targetNodePrimaryKey) {
	if (NULL == root || targetNodePrimaryKey == root->primaryKey) { // SI l'arbre n'a pas de noeud OU que la racine est la cible...
		return root; // ...retourner la racine.
	}
	if (root->primaryKey < targetNodePrimaryKey) { // SI la clé primaire du noeud actuel est plus petite que la clé primaire cible...
		return searchNodeViaPrimaryKey(root->rightChild, targetNodePrimaryKey); // ...chercher la clé primaire cible dans le noeud enfant droit.
	}
	return searchNodeViaPrimaryKey(root->leftChild, targetNodePrimaryKey); // Sinon, chercher la clé primaire cible dans le noeud enfant gauche.
}

/***********************************/
/**** Créer un noeud temporaire ****/
/***********************************/
stc_node *newNode(int value, char *first_name, char *last_name) {
	stc_node *node = malloc(sizeof(stc_node)); // Allocation de mémoire.
	if (NULL == node) {
		printf("Erreur d'allocation de mémoire");
		exit(EXIT_FAILURE);
	}
	node->primaryKey = value; // Assignation de la clé primaire.
	node->leftChild = NULL; // Assignation du pointeur à NULL.
	node->rightChild = NULL; // Assignation du pointeur à NULL.
	strcat(node->row.first_name, first_name); // Assignation du pointeur first_name.
	strcat(node->row.last_name, last_name); // Assignation du pointeur last_name.
	return node; // Retourner le pointeur vers le noeud créé.
}

/*****************************/
/***** Insérer un noeud  *****/
/*****************************/
stc_node *insertNode(stc_node *root, char *first_name, char *last_name) {
	int primaryKeyIndex = 1;
	
	while (NULL != searchNodeViaPrimaryKey(root, primaryKeyIndex)) { // TANT QUE la clé primaire existe...
		primaryKeyIndex += 1; // ...chercher une clé primaire plus grande.
	}

	root = insertNodeHelper(root, primaryKeyIndex, first_name, last_name); // Utiliser la clé primaire libre.
	
    	return root; // Retourner la racine de l'arbre mise à jour.
}

stc_node *insertNodeHelper(stc_node *node, int primaryKey, char *first_name, char *last_name) {
	if (node == NULL) { // SI le noeud n'existe pas...
		return newNode(primaryKey, first_name, last_name); // ...créer et retourner le noeud.
	}

	if (primaryKey < node->primaryKey) {
		node->leftChild = insertNodeHelper(node->leftChild, primaryKey, first_name, last_name); // Aller à gauche.
	} else if (primaryKey > node->primaryKey) {
		node->rightChild = insertNodeHelper(node->rightChild, primaryKey, first_name, last_name); // Aller à droite.
	}
	
	return node; // Retourner le noeud actuel.
}

/**********************************************/
/* Chercher le noeud ayant la plus petite clé */
/**********************************************/
stc_node *findNodeMinPrimaryKey(stc_node *root) {
	if (root == NULL) { // S'IL y a aucun noeud...
		return NULL;
	}
	else if (root->leftChild != NULL) { // SINON SI, il y a un noeud enfant gauche...
		return findNodeMinPrimaryKey(root->leftChild); //... rechercher à nouveau le noeud ayant la plus petit clé...
	}
	return root; // Retourner le noeud le plus petit.
}
 
/******************************************/
/* Supprimer un noeud via sa clé primaire */
/******************************************/
stc_node *deleteNode(stc_node *root,int toDeleteNodePrimaryKey) {
	if (root == NULL) { // S'IL y a aucun noeud...
		return NULL; 
	}
	/* Recherche du noeud à supprimer */
	if (toDeleteNodePrimaryKey > root->primaryKey) { // SI la clé du noeud à supprimer est plus grande que celle du noeud parcouru... 
		root->rightChild = deleteNode(root->rightChild, toDeleteNodePrimaryKey); // ...retenter une supression sur le noeud enfant droit.
	}
	else if (toDeleteNodePrimaryKey < root->primaryKey) { // SINON, SI la clé du noeud à supprimer est plus petite que celle du noeud parcouru... 
		root->leftChild = deleteNode(root->leftChild, toDeleteNodePrimaryKey); // ...retenter une supression sur le noeud enfant gauche.
	}
	/* Supression du noeud */
	else {
		if (root->leftChild == NULL && root->rightChild == NULL) { // SI le noeud n'a pas de noeud enfant...
			free(root); // ...supprimer le noeud.
			return NULL;
		}
		else if (root->leftChild == NULL || root->rightChild == NULL) { // SINON, SI le noeud a au moins un noeud enfant...
			stc_node *temp;
			if (root->leftChild == NULL) { // ...SI le noeud n'a pas de noeud enfant gauche...
				temp = root->rightChild; // ...conserver le pointeur du noeud enfant droit afin de le ré-attribuer au noeud parent.
			}
			else { // ...SINON le noeud n'a pas de noeud enfant droit...
				temp = root->leftChild; // ...donc, conserver le pointeur du noeud enfant gauche afin de le ré-attribuer au noeud parent.
			}
			free(root); // ...supprimer le noeud.
			return temp; // Retourner le noeud enfant, du noeud supprimé, au noeud précédent via l'appel récursif.
        	}
		else { // SINON, SI le noeud a deux noeuds enfants...
			stc_node *temp = findNodeMinPrimaryKey(root->rightChild); // ...chercher le noeud sucesseur, ayant la clé primaire la plus petite.
			root->primaryKey = temp->primaryKey; //...remplacer la clé primaire du noeud à supprimer par la clé primaire du sucesseur.
			root->rightChild = deleteNode(root->rightChild, temp->primaryKey); //...supprimer le noeud sucesseur.
		}
	}
	return root;
}

/******************************/
/****** Supprimer l'arbre *****/
/******************************/
void freeTree(stc_node *root) {
	if (root == NULL) { // SI l'abre est vide...
		return; //...ne rien faire.
	}

	/* Supprimer de manière récursive tous les neouds */
	freeTree(root->leftChild);
	freeTree(root->rightChild);

	free(root); // Libérer le noeud actuel.
}

/******************************/
/****** Afficher l'arbre *****/
/******************************/
void preOrderPrint(stc_node *root)
{
    if (root != NULL) {
        printf(" %d ", root->primaryKey);
        preOrderPrint(root->leftChild);
        preOrderPrint(root->rightChild);
    }
}

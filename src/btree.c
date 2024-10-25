/************************************************************************************/
/********************************** Bibliothèques ***********************************/
/************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "btree.h"
#include "avl.h"

/************************************************************************************/
/************************************* Fonctions ************************************/
/************************************************************************************/

/*****************************************/
/* Chercher un noeud via sa clé primaire */
/*****************************************/
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
		printf("Memory allocation failure occured !");
		exit(EXIT_FAILURE);
	}
	node->primaryKey = value; // Assignation de la clé primaire.
	node->height = 0; // Assignation de la hauteur du noeud à 0.
	node->leftChild = NULL; // Assignation du pointeur à NULL.
	node->rightChild = NULL; // Assignation du pointeur à NULL.
	strcpy(node->row.first_name, first_name); // Assignation du pointeur first_name.
	strcpy(node->row.last_name, last_name); // Assignation du pointeur last_name.
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
	//root = balanceTree(root); // Equilibrage AVL de l'arbre.
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
	node = updateNodeHeight(node); // Mettre à jour la hauteur du noeud.
	node = balanceTree(node); // Equilibrage AVL de l'arbre.
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

/**********************************************/
/* Chercher le noeud ayant la plus grande clé */
/**********************************************/
stc_node *findNodeMaxPrimaryKey(stc_node *root) {
	if (root == NULL) { // S'IL y a aucun noeud...
		return NULL;
	}
	else if (root->rightChild != NULL) { // SINON SI, il y a un noeud enfant droit...
		return findNodeMaxPrimaryKey(root->rightChild); //... rechercher à nouveau le noeud ayant la plus grande clé...
	}
	return root; // Retourner le noeud le plus grand.
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
	root = updateNodeHeight(root); // Mettre à jour la hauteur du noeud.
	root = balanceTree(root); // Equilibrage AVL de l'arbre.
	return root; // Retourne l'arbre.
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

/*****************************/
/****** Afficher l'arbre *****/
/*****************************/

void *showTree(char *userInput, stc_node *root) {
	/* Variables */
	int tableSize = countNodes(root);
	
	/* Fonctions */
	printf("\n");
	if (tableSize != 0) { // SI l'arbre n'est pas vide...
		if (strstr(userInput, "preorder") != NULL) { //...SI l'utilisateur à choisi de parcourir l'abre en preOrder...
			preOrderPrint(root);
		}
		else if (strstr(userInput, "inorder") != NULL) { //...SI l'utilisateur à choisi de parcourir l'abre en inOrder...
			inOrderPrint(root);
		}
		else if (strstr(userInput, "postorder") != NULL) { //...SI l'utilisateur à choisi de parcourir l'abre en postOrder...
			postOrderPrint(root);
		}
		else { // SINON, SI l'utilisateur n'a pas saisi d'argument valide...
			printf("Missing the expected argument.\n\n");
			printf("FORMAT : showtree type				TYPES : preorder");
		}
	}
	else { //...SINON, SI l'arbre est vide...
		printf("Tree is empty !");
	}
	printf("\n\n");
}

/*******************************************************************/
/****** Afficher l'arbre en preOrder (Racine - Gauche - Droite) ****/
/*******************************************************************/

void preOrderPrint(stc_node *root)
{
    if (NULL != root) {
        printf(" %d(h:%d) ", root->primaryKey, root->height);
        preOrderPrint(root->leftChild);
        preOrderPrint(root->rightChild);
    }
}

/*******************************************************************/
/****** Afficher l'arbre en inOrder (Gauche - Racine - Droite) ****/
/*******************************************************************/

void inOrderPrint(stc_node *root)
{
    if (NULL != root) {
        preOrderPrint(root->leftChild);
        printf(" %d(h:%d) ", root->primaryKey, root->height);
        preOrderPrint(root->rightChild);
    }
}

/*******************************************************************/
/****** Afficher l'arbre en inOrder (Gauche - Droite - Racine) ****/
/*******************************************************************/

void postOrderPrint(stc_node *root)
{
    if (NULL != root) {
        preOrderPrint(root->leftChild);
        preOrderPrint(root->rightChild);
        printf(" %d(h:%d) ", root->primaryKey, root->height);
    }
}

/******************************/
/****** Compter les noeuds ****/
/******************************/
int countNodes(stc_node *root)
{
    if (NULL == root)
        return 0;
 
    int left = countNodes(root->leftChild);
    int right = countNodes(root->rightChild);
 
    return 1 + left + right;
}

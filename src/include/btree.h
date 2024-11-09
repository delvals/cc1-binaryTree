#ifndef __BTREE_H__
#define __BTREE_H__

/************************************************************************************/
/********************************** Bibliothèques ***********************************/
/************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

/************************************************************************************/
/************************************** Typedef *************************************/
/************************************************************************************/

typedef struct row stc_row;
typedef struct node stc_node;

/************************************************************************************/
/************************************ Structures ************************************/
/************************************************************************************/

/***********************************/
/************ Ligne SQL ************/
/***********************************/
struct row {
	char first_name[50]; // Prénom.
	char last_name[50]; // Nom de famille.
};

/***********************************/
/************** Noeud **************/
/***********************************/
struct node {
  int primaryKey, height; // Clé primaire.
  stc_node *leftChild, *rightChild; // Pointeurs vers noeuds enfants.
  stc_row row; // Ligne SQL.
};

/************************************************************************************/
/************************************ Prototypes ************************************/
/************************************************************************************/

stc_node *searchNodeViaPrimaryKey(stc_node *root, int targetNodePrimaryKey);
stc_node *newNode(int value, char *first_name, char *last_name);
stc_node *insertNode(stc_node *root, char *first_name, char *last_name);
stc_node *insertNodeHelper(stc_node *node, int primaryKey, char *first_name, char *last_name);
stc_node *findNodeMinPrimaryKey(stc_node *root);
stc_node *findNodeMaxPrimaryKey(stc_node *root);
stc_node *deleteNode(stc_node *root,int toDeleteNodePrimaryKey);
void freeTree(stc_node *root);
void *showTree(char *userInput, stc_node *root);
void preOrderPrint(stc_node *root);
void inOrderPrint(stc_node *root);
void postOrderPrint(stc_node *root);
int countNodes(stc_node *root);

#endif

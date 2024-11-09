/************************************************************************************/
/********************************** Bibliothèques ***********************************/
/************************************************************************************/

#include "include/btree.h"

/************************************************************************************/
/************************************ Fonctions *************************************/
/************************************************************************************/

/***********************************************/
/***** Mettre à jour la hauteur d'un noeud *****/
/***********************************************/

stc_node *updateNodeHeight(stc_node *node) {
	if(NULL == node) {
		return node;
	}
	node->height = 0;
	if(NULL != node->leftChild) {
		node->height = node->leftChild->height + 1;
	}
	if((NULL != node->rightChild) && (node->rightChild->height >= node->height)) {
		node->height = node->rightChild->height + 1;
	}
	return node;
}

/**************************************/
/***** Rotation droite de l'arbre *****/
/**************************************/

stc_node *rotateTreeRight(stc_node *root) {
	stc_node *newRoot = root->leftChild;
	root->leftChild = newRoot -> rightChild;
	newRoot->rightChild = root;
	root = updateNodeHeight(root);
	newRoot = updateNodeHeight(newRoot);
	return newRoot;
}

/************************************/
/***** Rotation left de l'arbre *****/
/************************************/

stc_node *rotateTreeLeft(stc_node *root) {
	stc_node *newRoot = root->rightChild;
	root->rightChild = newRoot -> leftChild;
	newRoot->leftChild = root;
	root = updateNodeHeight(root);
	newRoot = updateNodeHeight(newRoot);
	return newRoot;
}

/**********************************/
/***** Equilibrage de l'arbre *****/
/**********************************/

int calculateBalanceIndex(stc_node *node) {
	if((NULL != node->leftChild) && (NULL != node->rightChild)) {
		return ((node->leftChild->height) - (node->rightChild->height));
	}
	else if ((NULL != node->leftChild)) {
		return ((node->leftChild->height) - 0);
	}
	else if ((NULL != node->rightChild)) {
		return (0 - (node->rightChild->height));
	}
	else {
		return 0;
	}
}

stc_node *balanceTree(stc_node *node) {
	if(NULL == node) {
		return node;
	}
	else if (calculateBalanceIndex(node) > 1) { // SI l'arbre penche trop à gauche...
		if (calculateBalanceIndex(node->leftChild) < 0) {
			node->leftChild = rotateTreeLeft(node->leftChild);
		}
		node = rotateTreeRight(node);
	}
	else if (calculateBalanceIndex(node) < -1) { // SINON, SI l'arbre penche trop à droite...
		if (calculateBalanceIndex(node->rightChild) > 0) {
			node->rightChild = rotateTreeRight(node->rightChild);
		}
		node = rotateTreeLeft(node);
	}
	else { // L'arbre ne penche pas.
		return node;
	}
}

#ifndef __QUERY_H__
#define __QUERY_H__

/************************************************************************************/
/********************************** Bibliothèques ***********************************/
/************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "cli.h"
#include "btree.h"
#include "save.h"

/************************************************************************************/
/************************************ Prototypes ************************************/
/************************************************************************************/

stc_node *insertNewRow(char *userInput, stc_node *liste_personnes);
void selectRow(char *userInput, stc_node *liste_personnes);
stc_node *deleteRow(char *userInput, stc_node *liste_personnes);

#endif

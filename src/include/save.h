#ifndef __SAVE_H__
#define __SAVE_H__

/************************************************************************************/
/********************************** Bibliothèques ***********************************/
/************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "save.h"
#include "btree.h"

/************************************************************************************/
/************************************ Prototypes ************************************/
/************************************************************************************/

stc_node *loadData(stc_node *liste_personnes);
void saveData(stc_node *liste_personnes);
void createSaveDirectory();

#endif
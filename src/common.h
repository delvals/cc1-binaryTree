#ifndef __COMMON_H__
#define __COMMON_H__

/************************************************************************************/
/********************************** Bibliothèques ***********************************/
/************************************************************************************/

#include <stdint.h>
#include "btree.h"

/************************************************************************************/
/************************************ Prototypes ************************************/
/************************************************************************************/

void emptyBuffer();
void clearScreen();
void readString(char *chaine, int longueur);
uint16_t findCharNumberInString(char *string, char searchedChar);
void replaceStringBy(char *string1, char *string2);

#endif

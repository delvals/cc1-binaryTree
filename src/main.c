/************************************************************************************/
/********************************** Bibliothèques ***********************************/
/************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "include/cli.h"
#include "include/save.h"

/************************************************************************************/
/************************************ Programme *************************************/
/************************************************************************************/

int main(int argc, char* argv[]) {
	
	/***** Fonctions *****/
	createSaveDirectory();
	executeCLI();
	
  	return 0;
}

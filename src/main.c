
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "print.h"
#include "minefield.h"

static uint16_t column = 0;
static uint16_t row = 0;

mineData_Typedef** ptrMirror = NULL;
mineData_Typedef** ptr=NULL;
int main(void) {

	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	column = 10;
	row = 5;
	initField(&ptr, row, column,true);
	/* in order to make comparement, initialize the same array */
	initField(&ptrMirror, row, column,false);
	/* fills up first array with random values */
	randomFill();
	PrintMineField(ptr, row, column,5,5);
	CalculateTheMinePossibility();
	changeVisibilityOfPossibilityMap(ptr, false);
	PrintMinePossibility(ptr, row, column, 5, 15,true);



	/*test*/
	constrainedCopy(ptrMirror, ptr, row, column);
	/*test*/
	PrintMinePossibility(ptrMirror, row, column, 25,15,false);





	return EXIT_SUCCESS;
}


/**
	@TODOs:

	* mines are created in random fashion						done
	* possibility map is created.								done
	* map cover which will be gradually makes the area visible	....
	* user interaction											....

*/
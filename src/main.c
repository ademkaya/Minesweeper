
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "print.h"
#include "minefield.h"

void intentionallyFill_Test(mineData_Typedef** _ptr, uint16_t row, uint16_t column);

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
	//randomFill();
	intentionallyFill_Test(ptr,row,column);

	PrintMineField(ptr, row, column,5,5);

	CalculateTheMinePossibility();
	changeVisibilityOfPossibilityMap(ptr, false);
	PrintMinePossibility(ptr, row, column, 5, 15,true);


	/*test*/
	constrainedCopy(ptrMirror, ptr, row, column);
	/*test*/
	PrintMinePossibility(ptrMirror, row, column, 25,15,false);

	checkMine(2, 2, true);

	return EXIT_SUCCESS;
}

void intentionallyFill_Test(mineData_Typedef** _ptr, uint16_t row, uint16_t column) {
	uint16_t c = 0;
	uint16_t r = 0;
	int rrr = 0;

	for (c = 0; c < column; c++) {
		for (r = 0; r < row; r++) {

			ptr[c][r].mine = false;
			ptr[c][r].mineVisibility = false;		/* as default hide all*/

		}
	}

	ptr[4][3].mine = true;

}

/**
	@TODOs:

	* mines are created in random fashion						done
	* possibility map is created.								done
	* map cover which will be gradually makes the area visible	....
	* user interaction											....

*/
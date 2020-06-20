
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "print.h"
#include "minefield.h"

static void ArrayTest(mineData_Typedef** ptr,uint32_t row,uint32_t column);
static uint32_t column = 0;
static uint32_t row = 0;

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


	memcpy(ptrMirror,ptr, sizeof(mineData_Typedef) * row * column);

		
		
	ArrayTest(ptr, row, column,5,5);
	ArrayTest(ptrMirror, row, column, 25, 5);
	
	return EXIT_SUCCESS;
}


static void ArrayTest(mineData_Typedef** ptr,uint32_t row,uint32_t column, uint8_t PrintXOffSet, uint8_t PrintYOffSet){

	int c=0;
	int r = 0;

	for (c = 0; c < column; c++) {
		for (r = 0; r < row; r++) {
			printCharOnSpesificLocation(PrintXOffSet + c, PrintYOffSet + r, (char)(0x30 + ptr[c][r].data));
		}
	}
}


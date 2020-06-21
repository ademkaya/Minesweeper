

	#include <stdio.h>		//puts
#include <stdlib.h>
#include <time.h>

#include "print.h"
#include "minefield.h"

#define mineBlock	(char)206
#define mineIcon	(char)'M'
#define nomineIcon	(char)'0'
static mineData_Typedef** staticPtr = NULL;
static uint32_t staticRow = 0;
static uint32_t staticColumn = 0;

static uint8_t Mchecker(int16_t xCalc, int16_t yCalc);

bool initField(mineData_Typedef*** ptr,uint16_t row, uint16_t column,bool AssignAsActual) {
	bool retVal = true;
	uint16_t cntr = 0;

	*ptr = (mineData_Typedef**)calloc(column, sizeof(mineData_Typedef*));
	if (!*ptr) {
		puts("Allocation Error");
		retVal = false;

	} else {

		for (cntr = 0; cntr < column; cntr++) {
			(*ptr)[cntr] = (mineData_Typedef*)calloc(row, sizeof(mineData_Typedef));
			if (!(*ptr)[cntr]) {
				puts("Allocation Error");
				retVal = false;
				break;
			}
		}
	}

	if (retVal && AssignAsActual) {
		staticPtr = *ptr;
		staticRow = row;
		staticColumn = column;
		srand((uint32_t)time(NULL));   // Initialization, should only be called once.
	}

	return retVal;
}

void PrintMineField(mineData_Typedef** ptr, uint16_t row, uint16_t column, uint8_t PrintXOffSet, uint8_t PrintYOffSet) {

	int c = 0;
	int r = 0;

	for (c = 0; c < column; c++) {
		for (r = 0; r < row; r++) {
			if (ptr[c][r].mine == true)
				printCharOnSpesificLocation(PrintXOffSet + c, PrintYOffSet + r, mineIcon);
			else
				printCharOnSpesificLocation(PrintXOffSet + c, PrintYOffSet + r, nomineIcon);
		}
	}
}
void PrintMinePossibility(mineData_Typedef** ptr, uint16_t row, uint16_t column, uint8_t PrintXOffSet, uint8_t PrintYOffSet,bool ActivateVisibility) {

	int c = 0;
	int r = 0;

	for (c = 0; c < column; c++) {
		for (r = 0; r < row; r++) {
			if (ActivateVisibility) {
				if (ptr[c][r].mineVisibility)
					printCharOnSpesificLocation(PrintXOffSet + c, PrintYOffSet + r, ptr[c][r].minePossibility);
				else
					printCharOnSpesificLocation(PrintXOffSet + c, PrintYOffSet + r, (char)mineBlock);
			} else {
				printCharOnSpesificLocation(PrintXOffSet + c, PrintYOffSet + r, ptr[c][r].minePossibility);
			}
		}
	}
}
/*1 - assigns Random mines onto the map.*/
void randomFill() {
	uint16_t c = 0;
	uint16_t r = 0;
	int rrr = 0;

	for (c = 0; c < staticColumn; c++) {
		for (r = 0; r < staticRow; r++) {

			staticPtr[c][r].mine = false;

			rrr = (int)rand() % 20;
			if (rrr == 10) {
				staticPtr[c][r].mine = true;
			}
			
		}
	}
}

void changeVisibilityOfPossibilityMap(mineData_Typedef** a,bool setVal) {
	uint16_t x = 0;
	uint16_t y = 0;

	for (x = 0; x < staticColumn; x++) {
		for (y = 0; y < staticRow; y++) {
			a[x][y].mineVisibility = setVal;
		}
	}
}

/* 2 - Checks the assigned mines and calculates the surrounding mine counts */
void CalculateTheMinePossibility(void) {
	uint16_t x = 0;
	uint16_t y = 0;
	uint8_t mineCount = 0;
	
	//  staticPtr[c][r].data = 'M';
	
	for (x = 0; x < staticColumn; x++) {
		for (y = 0; y < staticRow; y++) {

			mineCount = 0;
			mineCount += Mchecker(x + 1, y);
			mineCount += Mchecker(x + 1, y + 1);
			mineCount += Mchecker(x, y + 1);
			mineCount += Mchecker(x - 1, y + 1);
			mineCount += Mchecker(x - 1, y);
			mineCount += Mchecker(x - 1, y - 1);
			mineCount += Mchecker(x, y - 1);
			mineCount += Mchecker(x + 1, y - 1);
			staticPtr[x][y].minePossibility = (char)(0x30 + mineCount);

		}
	}
}
static uint8_t Mchecker(int16_t xCalc, int16_t yCalc) {
	bool skip = false;
	uint8_t retVal = 0;
		if ((xCalc < 0) || (yCalc < 0)) {
			skip = true;
		}
		if ((xCalc >= (int16_t)staticColumn) || (yCalc >= (int16_t)staticRow)) {
			skip = true;
		}

		if (!skip) {
			if (staticPtr[xCalc][yCalc].mine)
				retVal = 1;
		} else {
			retVal = 0;
		}

	return retVal;
}


/* user input comes here*/
bool checkMine(uint16_t row, uint16_t column,bool firstStart) {
	static uint16_t irow = 0;
	static uint16_t icolumn = 0;

	if (firstStart) {
		irow = row;
		icolumn = column;
	}

	/*selects the specified point and if no mines around it clears them*/

	/* NOT IMPLEMENTED YET */

	return false;
}

void constrainedCopy(mineData_Typedef** a, mineData_Typedef** b, uint16_t row, uint16_t column) {
	uint16_t c = 0;
	uint16_t r = 0;

	for (c = 0; c < column; c++) {
		for (r = 0; r < row; r++) {
			a[c][r].mine = b[c][r].mine;
			a[c][r].minePossibility = b[c][r].minePossibility;
		}
	}
}

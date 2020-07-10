

#include <stdio.h>		//puts
#include <stdlib.h>
#include <time.h>

#include "print.h"
#include "minefield.h"


static const char Hline		   = (char)205;
static const char Vline		   = (char)186;
static const char RTCornerline = (char)187;
static const char RBCornerline = (char)188;
static const char LTCornerline = (char)201;
static const char LBCornerline = (char)200;

static mineData_Typedef** staticPtr = NULL;
static uint16_t staticRow = 0;
static uint16_t staticColumn = 0;
static uint8_t staticPrintXOffSet = 0;
static uint8_t staticPrintYOffSet = 0;

static uint16_t totalMineCount = 0;
static uint16_t correctlyflaggedMineCount = 0;

static uint8_t Mchecker(int16_t xCalc, int16_t yCalc);
static bool limitsCheck(int16_t xCalc, int16_t yCalc);
static void SnakeframeCreation(uint8_t xOrigin, uint8_t yOrigin, uint16_t xLength, uint16_t yLength);

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

char PointerToggle(char keyPress, mineData_Typedef** mineStr, Coord_Typedef* ptr, uint8_t PrintXOffSet, uint8_t PrintYOffSet) {
	static uint16_t keyPressZeroCount = 0;
	static bool		IconToogle = false;

	if (keyPress == 0) {
		keyPressZeroCount += 1;
		if (keyPressZeroCount == ToogleConstant) {
			keyPressZeroCount = 0;
			if (!IconToogle) {
				if (mineStr[ptr->X][ptr->Y].mineVisibility) {
					if (!mineStr[ptr->X][ptr->Y].mineFlaggedByUser)
						printCharOnSpesificLocation(ptr->X + PrintXOffSet, ptr->Y + PrintYOffSet, WhiteColor, mineStr[ptr->X][ptr->Y].mergedMap);						
					else
						printCharOnSpesificLocation(ptr->X + PrintXOffSet, ptr->Y + PrintYOffSet, WhiteColor, flaggedMine);
				} else {
					if (!mineStr[ptr->X][ptr->Y].mineFlaggedByUser)
						printCharOnSpesificLocation(ptr->X + PrintXOffSet, ptr->Y + PrintYOffSet, WhiteColor, 0);
					else
						printCharOnSpesificLocation(ptr->X + PrintXOffSet, ptr->Y + PrintYOffSet, WhiteColor, flaggedMine);
				}
			}
			else {
				printCharOnSpesificLocation(ptr->X + PrintXOffSet, ptr->Y + PrintYOffSet, WhiteColor, pointerIcon);
			}
			IconToogle = !IconToogle;
		}

	}
	else {
		keyPressZeroCount = 0;
	}

	return keyPress;
}


//void PrintMineField(mineData_Typedef** ptr, uint16_t row, uint16_t column, uint8_t PrintXOffSet, uint8_t PrintYOffSet) {
//
//	int c = 0;
//	int r = 0;
//
//	for (c = 0; c < column; c++) {
//		for (r = 0; r < row; r++) {
//			if (ptr[c][r].mine == true)
//				printCharOnSpesificLocation(PrintXOffSet + c, PrintYOffSet + r, mineColor, mineIcon);
//			else
//				printCharOnSpesificLocation(PrintXOffSet + c, PrintYOffSet + r, WhiteColor, nomineIcon);
//		}
//	}
//
//	staticPrintXOffSet = PrintXOffSet;
//	staticPrintYOffSet = PrintYOffSet;
//
//	SnakeframeCreation(PrintXOffSet - 1, PrintYOffSet - 1, column+1, row+1);
//}

void PrintMergedMineField(mineData_Typedef** ptr, uint16_t row, uint16_t column, uint8_t PrintXOffSet, uint8_t PrintYOffSet,bool activateVisibility,bool isMineHit) {
	int c = 0;
	int r = 0;

	for (c = 0; c < column; c++) {
		for (r = 0; r < row; r++) {
			if (isMineHit) {

				if (!staticPtr[c][r].mineVisibility) {
					staticPtr[c][r].mineVisibility = true;
					staticPtr[c][r].mineFlaggedByUser = false;
					if (staticPtr[c][r].mine)
						printCharOnSpesificLocation(PrintXOffSet + c, PrintYOffSet + r, RedColor, staticPtr[c][r].mergedMap);
					else
						printCharOnSpesificLocation(PrintXOffSet + c, PrintYOffSet + r, WhiteColor, staticPtr[c][r].mergedMap);
				}
			} else {
				if (activateVisibility) {
					if (staticPtr[c][r].mineVisibility)
					{
						printCharOnSpesificLocation(PrintXOffSet + c, PrintYOffSet + r, WhiteColor, staticPtr[c][r].mergedMap);

					} else {

						printCharOnSpesificLocation(PrintXOffSet + c, PrintYOffSet + r, WhiteColor, (char)mineBlock);

					}

					if (staticPtr[c][r].mineFlaggedByUser) {
						printCharOnSpesificLocation(PrintXOffSet + c, PrintYOffSet + r, CyanColor, (char)flaggedMine);
					}

				} else {
					printCharOnSpesificLocation(PrintXOffSet + c, PrintYOffSet + r, WhiteColor, (char)mineBlock);
				}
			}
		}
	}

	staticPrintXOffSet = PrintXOffSet;
	staticPrintYOffSet = PrintYOffSet;

	SnakeframeCreation(PrintXOffSet - 1, PrintYOffSet - 1, column + 1, row + 1);
}

void EndGameCheer(void) {
	printStringOnSpesificLocation(staticPrintXOffSet+staticColumn/2, staticPrintYOffSet-2, RedColor, "!!! GAME OVER !!!");
	printStringOnSpesificLocation(0,0, WhiteColor, " ");
}
void WinnerCheer(void) {
	printStringOnSpesificLocation(staticPrintXOffSet , staticPrintYOffSet - 2, GreenColor, "Congratulations, You WON !!");
	printStringOnSpesificLocation(0, 0, WhiteColor, " ");
}
void PrintMinePossibility(mineData_Typedef** ptr, uint16_t row, uint16_t column, uint8_t PrintXOffSet, uint8_t PrintYOffSet,bool activateVisibility) {

	int c = 0;
	int r = 0;

	for (c = 0; c < column; c++) {
		for (r = 0; r < row; r++) {
			if (activateVisibility) {
				if (ptr[c][r].mineVisibility)
					printCharOnSpesificLocation(PrintXOffSet + c, PrintYOffSet + r, WhiteColor, ptr[c][r].minePossibility);
				else
					printCharOnSpesificLocation(PrintXOffSet + c, PrintYOffSet + r, WhiteColor, (char)mineBlock);
			} else {
				printCharOnSpesificLocation(PrintXOffSet + c, PrintYOffSet + r, WhiteColor, ptr[c][r].minePossibility);
			}
		}
	}
}

void changeVisibilityOfPossibilityMap(mineData_Typedef** a, bool revealtheFlagged,bool setVal) {
	uint16_t x = 0;
	uint16_t y = 0;

	for (x = 0; x < staticColumn; x++) {
		for (y = 0; y < staticRow; y++) {
			a[x][y].mineVisibility = setVal;
			if ((revealtheFlagged)&&((a[x][y].mineFlaggedByUser))){
				a[x][y].mineFlaggedByUser = false;
				a[x][y].mergedMap = (char)mineIcon;
			}
		}
	}
}

/* 2 - Checks the assigned mines and calculates the surrounding mine counts */
void CalculateTheMinePossibility(void) {
	uint16_t x = 0;
	uint16_t y = 0;
	uint8_t mineCount = 0;


	for (x = 0; x < staticColumn; x++)  {
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

			// visibility map and mine places are merged!
			if (staticPtr[x][y].mine) {
				staticPtr[x][y].mergedMap = (char)mineIcon;
			} else {
				staticPtr[x][y].mergedMap = staticPtr[x][y].minePossibility;
			}
		}
	}
}

/*1 - assigns Random mines onto the map.*/
void randomFill(void) {
	uint16_t c = 0;
	uint16_t r = 0;
	int rrr = 0;

	for (c = 0; c < staticColumn; c++) {
		for (r = 0; r < staticRow; r++) {

			staticPtr[c][r].mine = false;
			staticPtr[c][r].mineVisibility = false;		/* as default hide all*/

			rrr = (int)rand() % 20;
			if (rrr == 10) {
				staticPtr[c][r].mine = true;
				totalMineCount += 1;
			}
		}
	}
}

/* user input comes here*/
bool flagAction(int16_t crow, int16_t ccolumn,bool flagUnflag) {

	bool retVal = false;
	/*NOT COMPLETED YET!*/
	if (flagUnflag) {

		staticPtr[ccolumn][crow].mineFlaggedByUser = true;
		//.. print flaggedmine icon
		if (staticPtr[ccolumn][crow].mine)
		{
			correctlyflaggedMineCount += 1;
			if (correctlyflaggedMineCount == totalMineCount)
				retVal = true;
		}

	} else {

		staticPtr[ccolumn][crow].mineFlaggedByUser = false;
		if (staticPtr[ccolumn][crow].mine) {
			staticPtr[ccolumn][crow].mineVisibility = false;
			correctlyflaggedMineCount -= 1;			
		}
	}


	return retVal;
}

/* user input comes here*/
bool checkMine(int16_t crow, int16_t ccolumn,bool firstStart) {
	/* y,x*/
	static int16_t irow = 0;
	static int16_t icolumn = 0;

	/* scanning around the limits return	*/
	if (limitsCheck((int)ccolumn,(int)crow))
		return false;

	if (firstStart) {
		irow = crow;
		icolumn = ccolumn;

		/* check is the selected point is a mined point*/
		if (staticPtr[ccolumn][crow].mine)
			return true;	/* only in first input */
	}

	/* if the possibility is equal zero open them up until to the non-zero point */
	if ((staticPtr[ccolumn][crow].minePossibility == nomineIcon) && (!staticPtr[ccolumn][crow].mineVisibility)){
		staticPtr[ccolumn][crow].mineVisibility = true;

				checkMine(crow, ccolumn + 1, false);
				checkMine(crow + 1, ccolumn, false);
				checkMine(crow, ccolumn - 1, false);
				checkMine(crow - 1, ccolumn, false);

	}/* if the selection is a number which is different than zero and except the cell which includes mine */
	else if ((!staticPtr[ccolumn][crow].mine) && (!staticPtr[ccolumn][crow].mineVisibility)) {
		/* this is the end of the zero possiblity which must be a number more than zero */
		staticPtr[ccolumn][crow].mineVisibility = true;
	}

	return false;
}

static void SnakeframeCreation(uint8_t xOrigin, uint8_t yOrigin, uint16_t xLength, uint16_t yLength) {

	printCharOnSpesificLocation(xOrigin, yOrigin, WhiteColor, LTCornerline);
	printCharOnSpesificLocation(xOrigin + xLength, yOrigin, WhiteColor, RTCornerline);

	printCharOnSpesificLocation(xOrigin, yOrigin + yLength, WhiteColor, LBCornerline);
	printCharOnSpesificLocation(xOrigin + xLength, yOrigin + yLength, WhiteColor, RBCornerline);


	for (uint16_t x = 1; x < xLength; x++) {
		printCharOnSpesificLocation(xOrigin + x, yOrigin, WhiteColor, Hline);
		printCharOnSpesificLocation(xOrigin + x, yOrigin + yLength, WhiteColor, Hline);
	}
	for (uint16_t y = 1; y < yLength; y++) {
		printCharOnSpesificLocation(xOrigin, yOrigin + y, WhiteColor, Vline);
		printCharOnSpesificLocation(xOrigin + xLength, yOrigin + y, WhiteColor, Vline);
	}
}
/* VVVV STATICS COMES HERE VVVV */
static uint8_t Mchecker(int16_t xCalc, int16_t yCalc) {
	bool skip = false;
	uint8_t retVal = 0;
	
	skip = limitsCheck(xCalc,yCalc);

	if (!skip) {
		if (staticPtr[xCalc][yCalc].mine)
			retVal = 1;
	}
	else {
		retVal = 0;
	}

	return retVal;
}
static bool limitsCheck(int16_t xCalc, int16_t yCalc) {
	bool skip = false;
		if ((xCalc < 0) || (yCalc < 0)) {
			skip = true;
		}
		if ((xCalc >= (int16_t)staticColumn) || (yCalc >= (int16_t)staticRow)) {
			skip = true;
		}
	return skip;
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
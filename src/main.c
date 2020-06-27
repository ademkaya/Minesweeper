
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "print.h"
#include "minefield.h"


void GetRowColumnFromUser(int16_t* r, int16_t* c);
void intentionallyFill_Test(mineData_Typedef** _ptr, uint16_t row, uint16_t column);
void MovePointer(char keyPress, mineData_Typedef** mineStr, Coord_Typedef* ptr, uint8_t PrintXOffSet, uint8_t PrintYOffSet, uint16_t xLength, uint16_t yLength);

Coord_Typedef pointerCoord = { 0,0 };

static uint16_t column = 0;
static uint16_t row = 0;
static const uint8_t XOffset = 5;
static const uint8_t YOffset = 7;

mineData_Typedef** ptrMirror = NULL;
mineData_Typedef** ptr=NULL;
int main(void) {

	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	GetRowColumnFromUser(&row,&column);

	initField(&ptr, row, column, true);
	randomFill();
	CalculateTheMinePossibility();

	PrintMergedMineField(ptr, row, column, XOffset, YOffset,true);

	//nonblocking keypress detection will be 
	while (true)
	{
		char keyPress = NonBlockingKeyPressDetection();
		MovePointer(keyPress, ptr, &pointerCoord, XOffset, YOffset, column, row);

	}

	return EXIT_SUCCESS;
}
/**
		column = 10;
		row = 8;
		initField(&ptr, row, column,true);
		// in order to make comparement, initialize the same array
		initField(&ptrMirror, row, column, false);

		// fills up first array with random values/
		randomFill();
		//intentionallyFill_Test(ptr,row,column);

		PrintMineField(ptr, row, column, 5, 5);

		CalculateTheMinePossibility();
		changeVisibilityOfPossibilityMap(ptr, false);
		PrintMinePossibility(ptr, row, column, 5, 15, true);

		//test
		constrainedCopy(ptrMirror, ptr, row, column);
		//test
		PrintMinePossibility(ptrMirror, row, column, 25, 5, false);

		bool retVal = checkMine(2, 2, true);
		PrintMinePossibility(ptr, row, column, 5, 15, true);
*/

/* Guard is needed !*/
void GetRowColumnFromUser(int16_t* r, int16_t* c) {

	printf("Enter the ROW value of the field : ");
	scanf("%d", (int*)r);
	printf("Enter the COLUMN value of the field : ");
	scanf("%d", (int*)c);

	printf("%d %d", *r, *c);
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
	ptr[8][6].mine = true;
	ptr[6][6].mine = true;

}

void MovePointer(char keyPress, mineData_Typedef** mineStr,Coord_Typedef* ptr, uint8_t PrintXOffSet, uint8_t PrintYOffSet, uint16_t xLength, uint16_t yLength)
{

	static Coord_Typedef prePtr = { -1,-1 };
	static uint16_t keyPressZeroCount = 0;
	static bool		IconToogle = false;

	if ((prePtr.X == -1) && (prePtr.Y == -1)) {
		/* first call*/
		prePtr.X = PrintXOffSet;
		prePtr.Y = PrintYOffSet;
	}

	PointerToggle(keyPress, ptr, PrintXOffSet, PrintYOffSet);

	if (keyPress == 0) {
		return;
	}

	char normalizedKeyPress = toupper(keyPress);

	if ((normalizedKeyPress == direction_UP) && ((ptr->Y - 1) >= 0)) {
		ptr->X = ptr->X;
		ptr->Y -= 1;
	}

	if ((normalizedKeyPress == direction_DOWN) && ((ptr->Y + 1) < yLength)) {
		ptr->X = ptr->X;
		ptr->Y += 1;
	}

	if ((normalizedKeyPress == direction_RIGHT) && ((ptr->X + 1) < (xLength))) {
		ptr->X += 1;
		ptr->Y = ptr->Y;
	}

	if ((normalizedKeyPress == direction_LEFT) && ((ptr->X - 1) >= 0)) {
		ptr->X -= 1;
		ptr->Y = ptr->Y;
	}

	// recover back old icon back on the map
	if (mineStr[prePtr.X - PrintXOffSet][prePtr.Y - PrintYOffSet].mineVisibility) {
		printCharOnSpesificLocation(prePtr.X, prePtr.Y, mineStr[prePtr.X - PrintXOffSet][prePtr.Y - PrintYOffSet].mergedMap);
	}
	else {
		printCharOnSpesificLocation(prePtr.X, prePtr.Y, (char)mineBlock);
	}
	printCharOnSpesificLocation(ptr->X + PrintXOffSet, ptr->Y + PrintYOffSet, pointerIcon);
	prePtr.X = (ptr->X)+ PrintXOffSet;
	prePtr.Y = (ptr->Y)+ PrintYOffSet;

}








/**
	@TODOs:

	* mines are created in random fashion						done
	* possibility map is created.								done
	* map cover which will be gradually makes the area visible	done
	* user interaction											....

*/
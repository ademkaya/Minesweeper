
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "print.h"
#include "minefield.h"


void GetRowColumnFromUser(int16_t* r, int16_t* c);
void intentionallyFill_Test(mineData_Typedef** _ptr, uint16_t row, uint16_t column);
void MovePointer(char keyPress, mineData_Typedef** mineStr, Coord_Typedef* ptr, uint8_t PrintXOffSet, uint8_t PrintYOffSet, uint16_t xLength, uint16_t yLength);

/* public pointer coordinate, relative*/
static Coord_Typedef pointerCoord = { 0,0 };

static uint16_t column = 0;
static uint16_t row = 0;
static const uint8_t XOffset = 5;
static const uint8_t YOffset = 12;

mineData_Typedef** ptrMirror = NULL;
mineData_Typedef** ptr=NULL;
int main(void) {

	static char keyPress = 0;
	static char statickP = -1;
	static char mineResult = false;

	puts("\n\nHOW TO PLAY : \n - Flag the possible mine, pressing 'M' character \n - Reveal the area, pressing 'R' character\n" );

	GetRowColumnFromUser(&row,&column);

	initField(&ptr, row, column, true);
	randomFill();
	CalculateTheMinePossibility();

	PrintMergedMineField(ptr, row, column, XOffset, YOffset,true);

	//nonblocking keypress detection will be 
	while (true)
	{
		keyPress = toupper(NonBlockingKeyPressDetection());

		/* catch the keyboard input of instruction_OPEN */
		if (keyPress == instruction_OPEN) {
			if (!ptr[pointerCoord.X][pointerCoord.Y].mineFlaggedByUser)
				mineResult = checkMine(pointerCoord.Y, pointerCoord.X, true);
				if (mineResult) {
					ptr[pointerCoord.X][pointerCoord.Y].mineVisibility = true;  // temporary
					//...for now show the mine only... game finishes
				}
		} else if (keyPress == instruction_FLAG) {
				//.. flag action comes here
				flagAction(pointerCoord.Y, pointerCoord.X, true);

		} else if (keyPress == instruction_RemoveFLAG) {
			//...
		}

		/* move pointer inside the mine map*/
		MovePointer(keyPress, ptr,&pointerCoord, XOffset, YOffset, column, row);   // print part may be put outside of the function

		/*update the mine map when a key pressed*/
		if (statickP != keyPress) {
			PrintMergedMineField(ptr, row, column, XOffset, YOffset, true);
			statickP = keyPress;
		}
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

	//printf("%d %d", *r, *c);
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
	static Coord_Typedef prePointerPtr = { -1,-1 };
	static uint16_t keyPressZeroCount = 0;
	static bool		IconToogle = false;

	if ((prePointerPtr.X == -1) && (prePointerPtr.Y == -1)) {
		/* first call*/
		prePointerPtr.X = PrintXOffSet;
		prePointerPtr.Y = PrintYOffSet;
	}

	PointerToggle(keyPress, ptr, PrintXOffSet, PrintYOffSet);

	if (keyPress == 0) {
		return;
	}

	//char normalizedKeyPress = toupper(keyPress);

	if ((keyPress == direction_UP) && ((ptr->Y - 1) >= 0)) {
		ptr->X = ptr->X;
		ptr->Y -= 1;
	}

	if ((keyPress == direction_DOWN) && ((ptr->Y + 1) < yLength)) {
		ptr->X = ptr->X;
		ptr->Y += 1;
	}

	if ((keyPress == direction_RIGHT) && ((ptr->X + 1) < (xLength))) {
		ptr->X += 1;
		ptr->Y = ptr->Y;
	}

	if ((keyPress == direction_LEFT) && ((ptr->X - 1) >= 0)) {
		ptr->X -= 1;
		ptr->Y = ptr->Y;
	}

	// recover back old icon back on the map
	if (mineStr[prePointerPtr.X - PrintXOffSet][prePointerPtr.Y - PrintYOffSet].mineVisibility) {
		printCharOnSpesificLocation(prePointerPtr.X, prePointerPtr.Y, mineStr[prePointerPtr.X - PrintXOffSet][prePointerPtr.Y - PrintYOffSet].mergedMap);
	}
	else {
		printCharOnSpesificLocation(prePointerPtr.X, prePointerPtr.Y, (char)mineBlock);
	}
	printCharOnSpesificLocation(ptr->X + PrintXOffSet, ptr->Y + PrintYOffSet, pointerIcon);
	prePointerPtr.X = (ptr->X)+ PrintXOffSet;
	prePointerPtr.Y = (ptr->Y)+ PrintYOffSet;

}








/**
	@TODOs:

	* mines are created in random fashion								done
	* possibility map is created.										done
	* map cover which will be gradually makes the area visible			done
	* user interaction													partially done
	* [R]eveal interaction will be processed							done

	* [M]ine   interaction will be processed							continuing
	* totalMineCount is added will be resetted when a new game started	....
	* flagMine will be completed										....
	* unflagMine will be added											....
*/
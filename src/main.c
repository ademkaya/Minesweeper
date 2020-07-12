
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "print.h"
#include "minefield.h"


void GetRowColumnFromUser(int16_t* r, int16_t* c);
void intentionallyFill_Test(mineData_Typedef** _ptr, uint16_t row, uint16_t column);
void MovePointer(char keyPress, mineData_Typedef** mineStr, Coord_Typedef* ptr, uint8_t PrintXOffSet, uint8_t PrintYOffSet, uint16_t xLength, uint16_t yLength,bool IsgameFinishes);

/* public pointer coordinate, relative*/
static Coord_Typedef pointerCoord = { 0,0 };

static uint16_t column = 0;
static uint16_t row = 0;
static const uint8_t XOffset = 5;
static const uint8_t YOffset = 12;

//mineData_Typedef** ptrMirror = NULL;
mineData_Typedef** ptr=NULL;

static bool singleWriteRestartQuit = false;
static bool flagResult = false;
static bool mineResult = false;
static char keyPress = 0;
static char statickP = 0xFF;

int main(void) {

	restart:

	printStringOnSpesificLocation(0, 0, WhiteColor, " ");
	printf("%s %c %s %c %s", "\n\nHOW TO PLAY : \n - Flag the possible mine, pressing", instruction_FLAG, "character \n - Reveal the area, pressing", instruction_OPEN, "character\n");

	GetRowColumnFromUser(&row, &column);

	singleWriteRestartQuit = false;								/* clear the lock					  */		
	flagResult = false;											/* clear the result					  */
	mineResult = false;											/* clear the result					  */
	keyPress = (char) 0;										/* clear the var					  */
	statickP = (char) 0xFF;										/* clear the var					  */
	zeroTheMineCount();											/* clear the mine count				  */
	memset(&pointerCoord, 0, sizeof(Coord_Typedef));			/* clear the pointer coord			  */
	if (ptr) {
		clearPrvMineStr();										/* clear the previous mine field data */
	}

	initField(&ptr, row, column, true);
	randomFill();
	CalculateTheMinePossibility();

	PrintMergedMineField(ptr, row, column, XOffset, YOffset,true,false);

	while (true)
	{
		keyPress = toupper(NonBlockingKeyPressDetection());

		/* catch the keyboard input of instruction_OPEN */
		if (keyPress == instruction_OPEN) {
			if (!ptr[pointerCoord.X][pointerCoord.Y].mineFlaggedByUser)
				mineResult = checkMine(pointerCoord.Y, pointerCoord.X, true);
				if (mineResult) {
					/* END GAME */
					EndGameCheer();
				}
		} else if ((keyPress == instruction_FLAG) || (keyPress == instruction_RemoveFLAG)){
				//.. flag action comes here
			if (!ptr[pointerCoord.X][pointerCoord.Y].mineFlaggedByUser) {
				flagResult = flagAction(pointerCoord.Y, pointerCoord.X, true);
				if (flagResult) {
					// reveal the board .... 
					changeVisibilityOfPossibilityMap(ptr, true, true);
					// stop the toggling icon
					// -- gets into MovePointer via flagResult then stops the pointer
					// and congragulate the player
					WinnerCheer();
					// game successfully finishes...
					//...
				}
			} else {
				//.. unflag action comes here
					flagAction(pointerCoord.Y, pointerCoord.X, false);
			}
		}

		/* move pointer inside the mine map*/
		MovePointer(keyPress, ptr,&pointerCoord, XOffset, YOffset, column, row, flagResult|| mineResult);   // print part may be put outside of the function

		/*update the mine map when a key pressed*/
		if (statickP != keyPress) {
			PrintMergedMineField(ptr, row, column, XOffset, YOffset, true, mineResult);
			statickP = keyPress;
		}

		// restart questioning ..... 
		if (flagResult || mineResult) {	
			
			if (!singleWriteRestartQuit) {
				singleWriteRestartQuit = true;
				ShouldIRestartTheGame();
			}

			if (keyPress == RestartGame) {
				clearScreen();
				goto restart;
			}
			else if (keyPress == QuitGame) {
				clearScreen();
				break;
			}
		}

	}

	return EXIT_SUCCESS;
}

/* Guard is needed !*/
void GetRowColumnFromUser(int16_t* r, int16_t* c) {

	srand((uint32_t)time(NULL));   // Initialization, should only be called once.

	printf("Enter the ROW value of the field : ");
	scanf("%d", (int*)r);
	printf("Enter the COLUMN value of the field : ");
	scanf("%d", (int*)c);

	// zero input guard
	if (*r <= 0)
		*r = (int)rand() % 20;
	if (*c <= 0)
		*c = (int)rand() % 20;
	
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

void MovePointer(char keyPress, mineData_Typedef** mineStr,Coord_Typedef* ptr, uint8_t PrintXOffSet, uint8_t PrintYOffSet, uint16_t xLength, uint16_t yLength,bool IsgameFinishes)
{
	static Coord_Typedef prePointerPtr = { -1,-1 };
	static uint16_t keyPressZeroCount = 0;
	static bool		IconToogle = false;

	if ((prePointerPtr.X == -1) && (prePointerPtr.Y == -1)) {
		/* first call*/
		prePointerPtr.X = PrintXOffSet;
		prePointerPtr.Y = PrintYOffSet;
	}

	if (!IsgameFinishes)
		PointerToggle(keyPress, mineStr, ptr, PrintXOffSet, PrintYOffSet);
	else {
		if (!mineStr[ptr->X][ptr->Y].mine)
			printCharOnSpesificLocation(ptr->X + PrintXOffSet, ptr->Y + PrintYOffSet, WhiteColor, mineStr[ptr->X][ptr->Y].mergedMap);
		else
			printCharOnSpesificLocation(ptr->X + PrintXOffSet, ptr->Y + PrintYOffSet, RedColor, mineStr[ptr->X][ptr->Y].mergedMap);
	}
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
		printCharOnSpesificLocation(prePointerPtr.X, prePointerPtr.Y, WhiteColor, mineStr[prePointerPtr.X - PrintXOffSet][prePointerPtr.Y - PrintYOffSet].mergedMap);
	} else {
		printCharOnSpesificLocation(prePointerPtr.X, prePointerPtr.Y,WhiteColor, (char)mineBlock);
	}
	printCharOnSpesificLocation(ptr->X + PrintXOffSet, ptr->Y + PrintYOffSet, WhiteColor, pointerIcon);
	prePointerPtr.X = (ptr->X)+ PrintXOffSet;
	prePointerPtr.Y = (ptr->Y)+ PrintYOffSet;

}








/**
	@TODOs:

	* mines are created in random fashion									done
	* possibility map is created.											done
	* map cover which will be gradually makes the area visible				done	
	* [R]eveal interaction will be processed								done

	* [M]ine   interaction will be processed								done	
	* flagMine will be completed											done
	* unflagMine will be added												done
	* congragulate the player												done
	* game successfully finishes											done

	* PointerToggle will be stopped when the games completed				done
	* mine field will be visible on pointer toogling... now writes zero		done		
	* mine is hit end game loser											done
	* colorful Mine															done	
	* GetRowColumnFromUser ...  Guard is needed !							done
	* zero mine initialized  field											done
	* user interaction														done
	* Quit Restart game														done
	* totalMineCount is added will be resetted when a new game started		done
	* remove the zeros from the map text									....
	* clear the code														....
	* won game text coloring bug											....
*/
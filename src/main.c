
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "print.h"
#include "minefield.h"

#include <WinBase.h>
#include <consoleapi.h>



void GetRowColumnFromUser(int16_t* r, int16_t* c);
void intentionallyFill_Test(mineData_Typedef** _ptr, uint16_t row, uint16_t column);

static uint16_t column = 0;
static uint16_t row = 0;

mineData_Typedef** ptrMirror = NULL;
mineData_Typedef** ptr=NULL;
int main(void) {

	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	GetRowColumnFromUser(&row,&column);

	initField(&ptr, row, column, true);

	PrintMineField(ptr, row, column, 5, 7);

	//nonblocking keypress detection will be 


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

char NonBlockingKeyPressDetection(void) {
	char keyPress = 0;
	if (_kbhit())
	{
		keyPress = BlockingkeyPressDetection();
	}
	return keyPress;
}

/*--- Interaction ---*/
char BlockingkeyPressDetection(void) {
	static char ch = 0;
	getChar_(&ch);
	return(ch);
}

/*--- Interaction ---*/
bool getChar_(char* ch) {
	bool    ret = false;

	HANDLE  stdIn = GetStdHandle(STD_INPUT_HANDLE);

	DWORD   saveMode;
	GetConsoleMode(stdIn, &saveMode);
	SetConsoleMode(stdIn, ENABLE_PROCESSED_INPUT);

	if (WaitForSingleObject(stdIn, INFINITE) == WAIT_OBJECT_0)
	{
		DWORD num;
		ReadConsole(stdIn, ch, 1, &num, NULL);

		if (num == 1) ret = true;
	}

	SetConsoleMode(stdIn, saveMode);

	return(ret);
}

/*--- Interaction ---*/
void clearScreen(void) {
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
	system("clear");
#endif

#if defined(_WIN32) || defined(_WIN64)
	system("cls");
#endif
}







/**
	@TODOs:

	* mines are created in random fashion						done
	* possibility map is created.								done
	* map cover which will be gradually makes the area visible	done
	* user interaction											....

*/
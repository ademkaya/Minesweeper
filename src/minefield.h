#ifndef _MINEFIELD_H_
#define _MINEFIELD_H_

#include <stdint.h>
#include <stdbool.h>

#define mineBlock	(char)206
#define mineIcon	(char)'M'
#define nomineIcon	(char)'0'
#define flaggedMine	(char)176
#define endGame		(char)'X'



typedef struct mineData {
	bool mineVisibility;
	char minePossibility;
	bool mine;
	bool mineFlaggedByUser;
	char mergedMap;
}mineData_Typedef;


bool initField(mineData_Typedef*** ptr, uint16_t row, uint16_t column, bool AssignAsActual);

void PrintMineField(mineData_Typedef** ptr, uint16_t row, uint16_t column, uint8_t PrintXOffSet, uint8_t PrintYOffSet);
void PrintMinePossibility(mineData_Typedef** ptr, uint16_t row, uint16_t column, uint8_t PrintXOffSet, uint8_t PrintYOffSet, bool activateVisibility);
void PrintMergedMineField(mineData_Typedef** ptr, uint16_t row, uint16_t column, uint8_t PrintXOffSet, uint8_t PrintYOffSet, bool activateVisibility, bool isMineHit);

void constrainedCopy(mineData_Typedef** a, mineData_Typedef** b, uint16_t row, uint16_t column);
void CalculateTheMinePossibility(void);
void changeVisibilityOfPossibilityMap(mineData_Typedef** a, bool revealtheFlagged, bool setVal);
void randomFill(void);

void EndGameCheer(void);
void WinnerCheer(void);

char PointerToggle(char keyPress, mineData_Typedef** mineStr, Coord_Typedef* ptr, uint8_t PrintXOffSet, uint8_t PrintYOffSet);

bool checkMine(int16_t crow, int16_t ccolumn, bool firstStart);
bool flagAction(int16_t crow, int16_t ccolumn, bool flagUnflag);

#endif // !_MINEFIELD_H_

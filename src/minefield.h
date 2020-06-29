#ifndef _MINEFIELD_H_
#define _MINEFIELD_H_

#include <stdint.h>
#include <stdbool.h>

#define mineBlock	(char)206
#define mineIcon	(char)'M'
#define nomineIcon	(char)'0'
#define flaggedMine	(char)176

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
void PrintMergedMineField(mineData_Typedef** ptr, uint16_t row, uint16_t column, uint8_t PrintXOffSet, uint8_t PrintYOffSet, bool activateVisibility);

void constrainedCopy(mineData_Typedef** a, mineData_Typedef** b, uint16_t row, uint16_t column);
void CalculateTheMinePossibility(void);
void changeVisibilityOfPossibilityMap(mineData_Typedef** a, bool setVal);
void randomFill(void);

bool checkMine(int16_t crow, int16_t ccolumn, bool firstStart);
bool flagMine(int16_t crow, int16_t ccolumn);

#endif // !_MINEFIELD_H_

#ifndef _MINEFIELD_H_
#define _MINEFIELD_H_

#include <stdint.h>
#include <stdbool.h>


typedef struct mineData {
	bool processed;
	char minePossibility;
	bool mine;
}mineData_Typedef;


bool initField(mineData_Typedef*** ptr, uint16_t row, uint16_t column, bool AssignAsActual);
void PrintMineField(mineData_Typedef** ptr, uint16_t row, uint16_t column, uint8_t PrintXOffSet, uint8_t PrintYOffSet);
void constrainedCopy(char* a, char* b, uint16_t size);
void randomFill(void);

#endif // !_MINEFIELD_H_

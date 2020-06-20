#ifndef _MINEFIELD_H_
#define _MINEFIELD_H_

#include <stdint.h>
#include <stdbool.h>


typedef struct mineData {
	bool data;
}mineData_Typedef;


bool initField(mineData_Typedef*** ptr, uint32_t row, uint32_t column, bool AssignAsActual);
void randomFill(void);

#endif // !_MINEFIELD_H_



	#include <stdio.h>		//puts
#include <stdlib.h>
#include <time.h>

#include "minefield.h"

static mineData_Typedef** staticPtr = NULL;
static uint32_t staticRow = 0;
static uint32_t staticColumn = 0;

bool initField(mineData_Typedef*** ptr,uint32_t row, uint32_t column,bool AssignAsActual) {
	bool retVal = true;
	uint32_t cntr = 0;

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
		srand(time(NULL));   // Initialization, should only be called once.
	}

	return retVal;
}

void randomFill() {
	int c = 0;
	int r = 0;
	int rrr = 0;

	for (c = 0; c < staticColumn; c++) {
		for (r = 0; r < staticRow; r++) {
			rrr = (int)rand();
			staticPtr[c][r].data = (bool)(rrr % 2);
		}
	}
}


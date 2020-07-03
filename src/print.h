/*
 * File:   printf.h
 * Author: Adem
 *
 * Started on Jun , 2020, 22:22 PM
 */

#ifndef __PRINT_H__
#define __PRINT_H__

#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>


#ifdef __cplusplus
extern "C" {
#endif

#define ToogleConstant	(uint16_t)20000
#define pointerIcon		(char)219
#define direction_UP	(char)'W'
#define direction_DOWN	(char)'S'
#define direction_RIGHT (char)'D'
#define direction_LEFT	(char)'A'
#define instruction_FLAG		(char)'F'
#define instruction_RemoveFLAG	(char)'F'
#define instruction_OPEN		(char)'O'

	typedef struct coord {
		int16_t X;
		int16_t Y;
	}Coord_Typedef;

	void printCharOnSpesificLocation(uint16_t X, uint16_t Y, char chr);
	void printStringOnSpesificLocation(uint16_t X, uint16_t Y, char* str);
	char NonBlockingKeyPressDetection(void);
	char BlockingkeyPressDetection(void);
	void clearScreen(void);
	bool getChar_(char* ch);

#ifdef __cplusplus
}
#endif	/* __PRINT_H__ */
#endif
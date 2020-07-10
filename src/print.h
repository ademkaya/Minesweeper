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

#define RedColor			(uint8_t)91
#define WhiteColor			(uint8_t)97
#define GreenColor			(uint8_t)92
#define YellowColor			(uint8_t)93
#define BlueColor			(uint8_t)94
#define CyanColor			(uint8_t)96

#define BackRedWhiteFont	(uint8_t)41
#define BackGreenWhiteFont	(uint8_t)42
#define BackYellowWhiteFont	(uint8_t)43
#define BackBlackWhiteFont	(uint8_t)49

	typedef struct coord {
		int16_t X;
		int16_t Y;
	}Coord_Typedef;

	void printStringOnSpesificLocation(uint16_t X, uint16_t Y, uint8_t color, char* str);
	void printCharOnSpesificLocation(uint16_t X, uint16_t Y, uint8_t color, char chr);
	char NonBlockingKeyPressDetection(void);
	char BlockingkeyPressDetection(void);
	void clearScreen(void);
	bool getChar_(char* ch);

#ifdef __cplusplus
}
#endif	/* __PRINT_H__ */
#endif
#include <Windows.h>
#include "print.h"
#include <conio.h>


void printCharOnSpesificLocation(uint16_t X, uint16_t Y, char chr);
void printStringOnSpesificLocation(uint16_t X, uint16_t Y, char* str);
char NonBlockingKeyPressDetection(void);
char BlockingkeyPressDetection(void);
void clearScreen(void);
bool getChar_(char* ch);



/*--- Interaction ---*/
void printStringOnSpesificLocation(uint16_t X, uint16_t Y, char* str) {
    printf("\337\33[%d;%dH%s\338", Y, X, str);
}
/*--- Interaction ---*/
void printCharOnSpesificLocation(uint16_t X, uint16_t Y, char chr) {
    printf("\337\33[%d;%dH%c\338", Y, X, chr);
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
char BlockingkeyPressDetection(void){
    static char ch = 0;
    getChar_(&ch);
    return(ch);
}

/*--- Interaction ---*/
bool getChar_(char* ch){
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



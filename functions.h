// Header file for functions.c
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <stdarg.h>
#include <strings.h>
#include <stdbool.h>
#include <time.h>

#define MAX_X 30  // 29 
#define MAX_Y 14  // 13
// #define DEBUG

void intro(char *mode, bool *userTurn, char *userChar, char *oppChar, bool *introd);
bool makeToss(char mode);
char setGrid(int x, int y, int selected_col, char userChar);

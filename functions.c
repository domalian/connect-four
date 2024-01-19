#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <stdarg.h>
#include <strings.h>
#include <stdbool.h>
#include <time.h>
#include "functions.h"

bool makeToss(char mode) {
  int toss;
  bool userTurn;
  
  toss = rand() % 2;
  if(toss == 1){
    if(mode == '1') {
      printw("Player 1 will go first.\n");
    } else {
      printw("Player will go first.\n");
    }
    userTurn = true;
  } else {          
    if(mode == '1') {
      printw("Player 2 will go first.\n");
    } else {
      printw("Computer will go first.\n");
    }
    userTurn = false;
  }
  return userTurn;
}

void intro(char *mode, bool *userTurn, char *userChar, char *oppChar, bool *introd) {
  // Player or Computer? (User against selected player)
  printw("Press '1' to play against a player, and '0' to play against a computer.\n");
  *mode = getch();
  while(*mode != '1' && *mode != '0') {
    *mode = getch();
  }
  // If mode 1, player plays against another player. Else, they'll play against a computer
  if(*mode == '1') {
    printw("You will play against another player.\nPlayer 1: ");
  } else {
    printw("You will play against a computer. \nPlayer: ");
  }

  // X or O? (Game Pieces)
  printw("Press 'X' or 'O' to play as the corresponding piece.\n");
  *userChar = getch();
  while(*userChar != 'X' && *userChar != 'O' && *userChar != 'o' && *userChar != 'x') {
    *userChar = getch();
  }
  if(*userChar == 'o' || *userChar == 'O') {
    *userChar = 'O';
    *oppChar = 'X';
  } else {
    *userChar = 'X';
    *oppChar = 'O';
  }
  if(*mode == '1') {
    printw("Player 1 will play as %c, and Player 2 will play as %c.\n", *userChar, *oppChar);      
  } else {
    printw("Player will play as %c, and Computer will play as %c.\n", *userChar, *oppChar);
  }
  //Randomizer to determine who will go first
  *userTurn = makeToss(*mode);
  
  printw("Press any key to continue.\n");
  getch();
  clear();
}

char setGrid(int x, int y, int selected_col, char userChar) {
  char gridValue;

  if(y != 0  && (y % 2 == 0)) {
    if(x == 0 || (x % 4 == 0)) {
      gridValue = '|';
    } else {
      gridValue = ' ';
    }
  } else if(y != 0 ){
    if(x == 0 || x % 4 == 0) {
      gridValue = '+';
    } else {
      gridValue = '-';
    }
  } else {
    if(x == selected_col) {
      gridValue = userChar;
    } else {
      gridValue = ' ';
    }
  }

  return gridValue;
}

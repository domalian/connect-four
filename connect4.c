#include "functions.h"

// compile gcc connect4.c functions.c -lcurses
  
int main() {
  initscr();
  keypad(stdscr, TRUE);
  srand(time(0));
  cbreak();
  noecho();
  refresh();
  nl();

  int x, y, selected_col = 14, fill = 0; // User starts at middle
  int userWin = 0, oppWin = 0, draw = 0;
  
  char grid[MAX_X][MAX_Y], userKey, userChar, oppChar, mode, playAgain;
  bool gameON = true, userTurn = true, introd = true, end = false; // UserTurn is the player (if against computer) or player 1 (if against another player)

  // Function to play the intro
  intro(&mode, &userTurn, &userChar, &oppChar, &introd);

  // While loop for the entire game
  while(end != true) {
    printw("\t\t\t    CONNECT 4\n\tUSE A/D KEYS TO MOVE, AND SPACEBAR TO DROP THE DISC.\n\n\t\t");

    /////////// Arrays are very confusing. When grid[x][13], memory overlaps with grid[x][0]
    for(y = 0; y <= MAX_Y - 1; y++) { // Setting grid pre-userinput
      for(x = 0; x <= MAX_X - 2; x++) {
        grid[x][y] = setGrid(x, y, selected_col, userChar);
        printw("%c", grid[x][y]);
      }

      if(x == 29) {
        grid[x][y] = '\n';
        printw("%c", grid[x][y]);
      }

#ifdef DEBUG // DEBUG grid
    for(y = 0; y <= MAX_Y; y++) {
      for(x = 0; x <= MAX_X; x++) {
        printw("%c", grid[x][y]);
        printw("x = %i, y = %i",x, y);
        getch();
      }
      printw("\n\t\t");
      printw("%i", y);
      getch();
    }
    getch();
#endif
    }


    while(gameON) { // While the round is ON
      if(!introd) { // Skip user input for the first loop
        if(userTurn || mode == '1') {
          userKey = getch();
        } else { // Computer turn --> randomize move
          selected_col = 2 + ((rand() % 7) * 4);
          while(grid[selected_col][2] != ' ') {
            selected_col = 2 + ((rand() % 7) * 4);
          }
          userKey = ' ';
        }
      } else {
        introd = false;
      }

      // Check for user's input
      switch(userKey) {
        case 'A': // Move disc to the left when A is pressed
        case 'a':
          if(selected_col > 2 && selected_col <= MAX_X - 4) { // If the disc has room to move left
            selected_col = selected_col - 4;
          }
          
          if(userTurn) { // Assign the dropped disc according to whose turn it is
            grid[selected_col][0] = userChar;
          } else {
            grid[selected_col][0] = oppChar;
          }
          break;

        case 'D': // Move disc to the right when D is pressed
        case 'd':
          if(selected_col >= 2 && selected_col < MAX_X - 4) { // If the disc has room to move right
            selected_col = selected_col + 4;
          }

          if(userTurn) { // Assign the dropped disc according to whose turn it is
            grid[selected_col][0] = userChar;
          } else {
            grid[selected_col][0] = oppChar;
          }
          break;

        case ' ': // Drop the disc when SPACE is pressed
          for(y = 12; grid[selected_col][y] != ' ' && y > 2; y = y - 2) { 
            // For loop to check which row is empty
          } 
          
          if(grid[selected_col][y] == ' ') { // If a row of the selected column is empty, drop the disc
            if(userTurn) {
              grid[selected_col][y] = userChar;
              grid[selected_col][0] = oppChar; // Sets position of next player's disk in the middle (?)
              userTurn = false;
            } else {
              grid[selected_col][y] = oppChar;
              grid[selected_col][0] = userChar;
              userTurn = true; // Sets position of next player's disk in the middle (?
            }
          } else {
            if(userTurn) {
              grid[selected_col][0] = userChar; 
            } else {
              grid[selected_col][0] = oppChar;
            }
          }
          break;

        default:
        if(userTurn) {
          grid[selected_col][0] = userChar;
        } else {
          grid[selected_col][0] = oppChar;
        }
        break;
      }

      clear(); // Clear screen
      printw("\t\t\t    CONNECT 4\n\tUSE A/D KEYS TO MOVE, AND SPACEBAR TO DROP THE DISC.\n\n\t\t"); // Title

      for(y = 0; y <= MAX_Y - 1; y++) { // Print out the grid
        for(x = 0; x <= MAX_X - 2; x++) {
          printw("%c", grid[x][y]);
        }
        printw("\n\t\t");
      }

      for(x = 2; x <= 26; x = x + 4) { // Reset the row above the grid to prevent stray characters
        grid[x][0] = ' ';
      }

      // Win check: Horizontal, vertical, ascending diagonal, descending diagonal check
      for(y = MAX_Y - 2; y >= 2 && gameON; y = y - 2) {
        for(x = MAX_X - 4; x >= 2 && gameON; x = x - 4) {
          if(grid[x][y] != ' ') {
            if((grid[x][y] == grid[x - 4][y] && grid[x][y] == grid[x - 8][y] && grid[x][y] == grid[x - 12][y]) || (grid[x][y] == grid[x][y - 2] && grid[x][y] == grid[x][y - 4] && grid[x][y] == grid[x][y - 6]) || (grid[x][y] == grid[x - 4][y - 2] && grid[x][y] == grid[x - 8][y - 4] && grid[x][y] == grid[x - 12][y - 6]) || (grid[x][y] == grid[x + 4][y - 2] && grid[x][y] == grid[x + 8][y - 4] && grid[x][y] == grid[x + 12][y - 6])){

              if(grid[x][y] == userChar) { // 1st player or Player wins
                if(mode == '1'){
                  printw("Player 1 wins!\n\n\t\t"); 
                } else {
                  printw("Player wins!\n\n\t\t");
                }
                userWin ++;
              } else { // 2nd player or Computer wins
                if(mode == '1') {
                  printw("Player 2 wins!\n\n\t\t");
                } else {
                  printw("Computer wins!\n\n\t\t");
                }
                oppWin++;
              }

#ifdef DEBUG
                printw("x = %i; y = %i\n", x, y);
                getch();
#endif

              gameON = false;
            // Count for how many spaces are filled in first row
            } else if(y == 2 && grid[x][y] != ' '){
              fill ++;
            }
          }
        }
      }

      // Check if the first row is full
      if(fill >= 7 && gameON) {
        printw("It's a draw!\n\n\t\t");
        gameON = false;
        draw++;
      }
      fill = 0;

      // Print out the scores: (Player 1 vs Player 2) and (Player vs Computer) 
      if(mode == '1') {
        printw("%c Player 1: %i\n\t\t%c Player 2: %i\n\t\t", userChar, userWin, oppChar, oppWin);
      } else {
        printw("%c    Player: %i\n\t\t%c Computer: %i\n\t\t", userChar, userWin, oppChar, oppWin);
      }
      printw("      Draw: %i\n\n\t\t", draw);

    } // End of round loop
  
    // Play again?
    printw("Press 1 to play again, and 0 to exit.\n");
    playAgain = getch();
    while(playAgain != '0' && playAgain != '1') {
      playAgain = getch();
    }
    
    // Condition check if the player wants to play again
    if(playAgain == '1') {
      gameON = true;
      userKey = '1';
      clear();
      userTurn = makeToss(mode);
      printw("Press any key to continue.\n");
      getch();
      introd = true;
    } else {
      end = true;
    }

   } // End of game loop

  endwin();
  return 0;

}

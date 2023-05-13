#include <stdio.h>

#define BOARD_SIZE 8
#define SHIP_LENGTH 5
#define EMPTY_IDENTIFIER '~'

const char* LETTERS = "ABCDEFGHIJKLMNOPQRST";

int board[BOARD_SIZE][BOARD_SIZE];

void initBoard() {
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++)
      board[i][j] = 0;
  }
}

void drawBoard() {
  printf("  ");
  for (int i = 0; i < BOARD_SIZE; i++) {
    printf("%d ", i + 1);
  }
  printf("\n");

  for (int i = 0; i < BOARD_SIZE; i++) {
    printf("%c ", LETTERS[i]);
    for (int j = 0; j < BOARD_SIZE; j++) {
      if (board[i][j] == 0)
        printf("%c ", EMPTY_IDENTIFIER);
      else
        printf("%d ", board[i][j]);
    }
    printf("\n");
  }
}

int buildShip(int startsAtColumn, int startsAtRow, char orientation) {  
  for (int i = startsAtColumn; i < SHIP_LENGTH + startsAtColumn; i++) {
    if (orientation == 'v') {
      board[startsAtRow - 1][i - 1] = 1;
    } else {
      board[i - 1][startsAtColumn - 1] = 1;
    }
  }

  return 1;
}

int main() {
  initBoard();
  buildShip(3, 3, 'h');
  drawBoard();

  return 0;
}
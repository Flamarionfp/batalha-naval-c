#include <stdio.h>

#define BOARD_SIZE 8
#define SHIP_LENGTH 3
#define SHIP_LIMIT 1
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

void buildShip(int startsAtColumn, int startsAtRow, char orientation) {  
  printf("%c\n", orientation);

  for (int i = startsAtColumn; i < SHIP_LENGTH + startsAtColumn; i++) { 
    if (orientation == 'h') {
      board[startsAtRow - 1][i - 1] = 1;
    } else {
      board[i - 1][startsAtColumn - 1] = 1;
    }
  }
}

// int checkValidPosition(int startsAtColumn, int startsAtRow, char orientation) {
//   // implementar essa lógica
//   return 1;
// }

// usar depois para validar a orientação
// int checkValidOrientationLabel(char orientation) {
//   if (orientation == 'v' || orientation == 'h') {
//     return 1;
//   }

//   return 0;
// }

void askForBuildShips() {
  int startsAtColumn, startsAtRow;
  int i = 0;
  char orientation;

  while (i < SHIP_LIMIT) {
    printf("Informe a linha inicial do navio: ");
    scanf("%d", &startsAtRow);

    printf("Informe a coluna inicial do navio: ");
    scanf("%d", &startsAtColumn);

    printf("Informe a orientacao do navio (v - vertical, h - horizontal): ");
    scanf(" %c", &orientation);

    buildShip(startsAtColumn, startsAtRow, orientation);
    drawBoard();

    i++;
  }
}

int main() {
  initBoard();
  askForBuildShips();
  return 0;
}
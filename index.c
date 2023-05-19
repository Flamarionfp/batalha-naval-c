// Trabalho Flamarion Fagundes e Allan Rizi

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define BOARD_SIZE 9
#define SHIP_LENGTH 5
#define SHIP_LIMIT 2
#define SHOTS_LIMIT 2
#define EMPTY_IDENTIFIER '~'

const char* LETTERS = "ABCDEFGHIJKLMNOPQRST";

int board[BOARD_SIZE][BOARD_SIZE];

void clearScreen() {
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}

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
      else {
        printf("%d ", board[i][j]);
      }
    }
    printf("\n");
  }
}

void buildShip(int startsAtColumn, int startsAtRow, char orientation) {  
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

void askToBuildShips() {
  int startsAtColumn, startsAtRow, currentShip;
  int i = 0;
  char orientation;

  while (i < SHIP_LIMIT) {
    currentShip = i + 1;

    printf("Informe a linha inicial do navio %d: ", currentShip);
    scanf("%d", &startsAtRow);

    printf("Informe a coluna inicial do navio %d: ", currentShip);
    scanf("%d", &startsAtColumn);

    printf("Informe a orientacao do navio %d (v - vertical, h - horizontal): ", currentShip);
    scanf(" %c", &orientation);

    buildShip(startsAtColumn, startsAtRow, orientation);
    drawBoard();

    i++;
  }
}

int verifyPlayAgain(char playAgain[]) {
  return strcasecmp(playAgain, "sair") != 0;
}


void makePlay() {
  
}

void askToPlay() {
  int shotsRemaining = SHOTS_LIMIT;
  int row, column;

  while (shotsRemaining > 0) {
    printf("Informe a linha do tiro: ");
    scanf("%d", &row);

    printf("Informe a coluna do tiro: ");
    scanf("%d", &column);

    makePlay();
    drawBoard();

    shotsRemaining--;
  }
}

int main() {
  char playAgain[100];

  do {
    printf("Batalha Naval\n\n");
    initBoard();
    askToBuildShips();
    sleep(2); // adicionei esse sleep para o jogador poder ver o último barco posicionado antes de limpar a tela
    clearScreen();
    initBoard();
    drawBoard();
    askToPlay();

    printf("Jogar novamente ou sair? ");
    scanf("%s", playAgain);

  } while(verifyPlayAgain(playAgain));
  
  return 0;
}
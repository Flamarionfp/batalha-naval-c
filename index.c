// Trabalho Flamarion Fagundes e Allan Rizi

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define BOARD_SIZE 9
#define SHIP_LENGTH 5
#define SHIP_LIMIT 1
#define SHOTS_LIMIT 2
#define SHIPS_DESTROYED_TO_WIN 1
#define EMPTY_IDENTIFIER '~'
#define SHIP_IDENTIFIER '#'
#define SHOT_IDENTIFIER '*'

const char* LETTERS = "ABCDEFGHIJKLMNOPQRST";

int shipBoard[BOARD_SIZE][BOARD_SIZE];
int shotBoard[BOARD_SIZE][BOARD_SIZE];
int shipsDestroyed = 0;

// isso aqui vai ser definido a nível de compilação para rodar o comando de limpar a tela de acordo com a plataforma
void clearScreen() {
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}

void askToClearScreen() {
    char shouldClearScreen = 'n';

    while (shouldClearScreen != 'v' && shouldClearScreen != 'V') {
      printf("Pressione a tecla v para limpar a tela: \n");
      scanf(" %c", &shouldClearScreen);

      if (shouldClearScreen == 'v' || shouldClearScreen == 'V') {
        clearScreen();
      }
    }
}

void initBoards() {
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      shipBoard[i][j] = 0;
      shotBoard[i][j] = 0;
    }
  }
}

// se der tempo, refatorar essa função para simplificar as condições (quebrar em funções menores)
void drawBoard(int isShipBoard) {
  printf("  ");
  for (int i = 0; i < BOARD_SIZE; i++) {
    printf("%d ", i + 1);
  }
  printf("\n");

  for (int i = 0; i < BOARD_SIZE; i++) {
    printf("%c ", LETTERS[i]);
    for (int j = 0; j < BOARD_SIZE; j++) {
      if (isShipBoard) {
        if (shipBoard[i][j] == 0)
          printf("%c ", EMPTY_IDENTIFIER);
        else
          printf("%c ", SHIP_IDENTIFIER);
      } else {
        if (shotBoard[i][j] == 0)
          printf("%c ", EMPTY_IDENTIFIER);
        else if (shotBoard[i][j] == 1)
          printf("%c ", SHOT_IDENTIFIER);
        else if (shotBoard[i][j] == 2)
          printf("%c ", SHIP_IDENTIFIER);
      }
    }
    printf("\n");
  }
}

void buildShip(int startsAtColumn, int startsAtRow, char orientation) {  
  for (int i = startsAtColumn; i < SHIP_LENGTH + startsAtColumn; i++) { 
    if (orientation == 'h') {
      shipBoard[startsAtRow - 1][i - 1] = 1;
    } else {
      shipBoard[i - 1][startsAtColumn - 1] = 1;
    }
  }
}

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
    drawBoard(1); 

    i++;
  }
}

int verifyPlayAgain(char playAgain[]) {
  return strcasecmp(playAgain, "sair") != 0;
}

// int verifyWin() {
//   return shipsDestroyed == SHIPS_DESTROYED_TO_WIN;
// }

void makePlay(int row, int column) {
  if (shipBoard[row - 1][column - 1] == 1) {
    printf("Acertou!\n");
    shipBoard[row - 1][column - 1] = 2; // aqui pode ser qualquer coisa diferente de 0 (vazio) e 1 (navio) 
    shotBoard[row - 1][column - 1] = 1;
  } else {
    printf("Errou!\n");
    shotBoard[row - 1][column - 1] = 1;
  }
}

void askToPlay() {
  int shotsRemaining = SHOTS_LIMIT;
  int row, column;

  while (shotsRemaining > 0) {
    printf("Informe a linha do tiro: ");
    scanf("%d", &row);

    printf("Informe a coluna do tiro: ");
    scanf("%d", &column);

    makePlay(row, column);
    drawBoard(0);  

    shotsRemaining--;
  }
}

int main() {
  char playAgain[100];
  // int win;

  do {
    printf("Batalha Naval\n\n");
    initBoards();
    askToBuildShips();
    sleep(2); // Adicionei esse sleep para o jogador poder ver o último barco posicionado antes de limpar a tela
    askToClearScreen();
    drawBoard(0);  
    askToPlay();

    // win = verifyWin();

    // if (win) {
    //   printf("Voce venceu!\n");
    // } else {
    //   printf("Voce perdeu!\n");
    // }

    printf("Jogar novamente ou sair? ");
    scanf("%s", playAgain);

  } while (verifyPlayAgain(playAgain));
  
  return 0;
}

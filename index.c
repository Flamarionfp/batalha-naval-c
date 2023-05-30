#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define BOARD_SIZE 20
#define SHIP_LENGTH 5
#define SHIP_LIMIT 3
#define SHOTS_LIMIT 30
#define EMPTY_IDENTIFIER '~'
#define SHIP_IDENTIFIER '#'
#define SHOT_IDENTIFIER 'O'
#define MISS_IDENTIFIER 'X'

const char* LETTERS = "ABCDEFGHIJKLMNOPQRST";

char players[2][100];
int currentPlayerIndex = 0;
int wonRoundsByPlayer[2];
int shipsDestroyedByPlayer[2] = {0, 0}; 
int positionsHitByPlayer[2];

int shipBoard[BOARD_SIZE][BOARD_SIZE];
int shotBoard[BOARD_SIZE][BOARD_SIZE];
int hasDestroyedAll = 0;

// isso aqui vai ser definido a nível de compilação para rodar o comando de limpar a tela de acordo com o ambiente de execução
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

void changePlayer() {
  currentPlayerIndex = currentPlayerIndex == 0 ? 1 : 0;
}

void initBoards() {
  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      shipBoard[i][j] = 0;
      shotBoard[i][j] = 0;
    }
  }
}

void drawBoard(int isShipBoard) {
  printf("   ");
  for (int i = 0; i < BOARD_SIZE; i++) {
    printf("%3d", i + 1); // adicionei o 3d pra ficar mais espaçado, como é 20x20 o tabuleiro
  }
  printf("\n");

  for (int i = 0; i < BOARD_SIZE; i++) {
    printf("%c  ", LETTERS[i]);
    for (int j = 0; j < BOARD_SIZE; j++) {
      if (isShipBoard) {
        if (shipBoard[i][j] == 0)
          printf("%3c", EMPTY_IDENTIFIER);
        else
          printf("%3c", SHIP_IDENTIFIER);
      } else {
        if (shotBoard[i][j] == 0)
          printf("%3c", EMPTY_IDENTIFIER);
        else if (shotBoard[i][j] == 1)
          printf("%3c", SHOT_IDENTIFIER);
        else if (shotBoard[i][j] == 2)
          printf("%3c", SHIP_IDENTIFIER);
        else {
          printf("%3c", MISS_IDENTIFIER);
        }
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

    printf("%s, informe a linha inicial do navio %d: ", players[currentPlayerIndex] ,currentShip);
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

int verifyLose() {
  return shipsDestroyedByPlayer[currentPlayerIndex] < SHIP_LIMIT;
}

void onWin() {
  wonRoundsByPlayer[currentPlayerIndex]++;
  shipsDestroyedByPlayer[currentPlayerIndex] += SHIP_LIMIT;

  printf("Jogador %s venceu!\n", players[currentPlayerIndex]);
}

void onLose() {
  printf("Jogador %s perdeu!\n", players[currentPlayerIndex]);
}

int checkDestroyedAllShips() {
  int shipsNotDestroyed = 0;

  for (int i = 0; i < BOARD_SIZE; i++) {
    for (int j = 0; j < BOARD_SIZE; j++) {
      if (shipBoard[i][j] == 1) {
        shipsNotDestroyed = 1;
        return 0;
      }
    }
    if (shipsNotDestroyed) {
      return 0;
    }
  }

  return !shipsNotDestroyed;
}

void onHitShot(int row, int column) {
  positionsHitByPlayer[currentPlayerIndex]++;
  printf("Acertou!\n");
  shipBoard[row - 1][column - 1] = 2; 
  shotBoard[row - 1][column - 1] = 1;
}

void onMissedShot(int row, int column) {
  printf("Errou!\n");
  shotBoard[row - 1][column - 1] = 3; // aqui pode ser qualquer coisa diferente de 0, 1, 2 - vazio, tiro, navio, para representar o erro do tiro
}

void makePlay(int row, int column) {
  if (shipBoard[row - 1][column - 1] == 1) {
    onHitShot(row, column);
  } else {
    onMissedShot(row, column);
  }
  
  hasDestroyedAll = checkDestroyedAllShips();

  if (hasDestroyedAll) {
    onWin();
  }
}

void askToPlay() {
  int shotsRemaining = SHOTS_LIMIT;
  int row, column;

  while (shotsRemaining > 0 && hasDestroyedAll != 1) {
    printf("%s, informe a linha do tiro: ", players[currentPlayerIndex]);
    scanf("%d", &row);

    printf("Informe a coluna do tiro: ");
    scanf("%d", &column);

    makePlay(row, column);
    drawBoard(0);  

    shotsRemaining--;
  }
}

void startGame() {
  printf("Batalha Naval\n\n");
  printf("Informe o nome do jogador 1: ");
  scanf("%s", players[0]);

  printf("Informe o nome do jogador 2: ");
  scanf("%s", players[1]);
}

void showGameReport() {
  printf("\n");
  for (int i = 0; i < 2; i++) {
    printf("\n");
    printf("Jogador %s acertou %d tiro(s)\n", players[i], positionsHitByPlayer[i]);
    printf("Jogador %s destruiu %d navio(s)\n", players[i], shipsDestroyedByPlayer[i]);
    printf("Jogador %s venceu %d rodada(s)\n", players[i], wonRoundsByPlayer[i]);
  }
}

int main() {
  char playAgain[100];
  int lose;

  startGame();

  do {
    initBoards();
    askToBuildShips();
    sleep(2); // Adicionei esse sleep para o jogador poder ver o último barco posicionado por alguns segundos antes de limpar a tela
    askToClearScreen();
    changePlayer(); // troca para o jogador que vai atirar
    drawBoard(0);  
    askToPlay();

    lose = verifyLose();

    if (lose) {
      onLose();
    }
    
    printf("Jogar novamente ou sair? ");
    scanf("%s", playAgain);
  } while (verifyPlayAgain(playAgain));

  showGameReport();
  
  return 0;
}
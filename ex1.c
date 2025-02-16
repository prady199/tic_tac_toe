#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 3

char board[SIZE][SIZE];
int difficulty = 1; // Difficulty level (1 = easy, increases with wins)

void initializeBoard() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = ' ';
        }
    }
}

void printBoard() {
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf(" %c ", board[i][j]);
            if (j < SIZE - 1) printf("|");
        }
        printf("\n");
        if (i < SIZE - 1) printf("---|---|---\n");
    }
    printf("\n");
}

int checkWin(char player) {
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return 1;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return 1;
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return 1;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return 1;
    return 0;
}

int isFull() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') return 0;
        }
    }
    return 1;
}

void playerMove() {
    int x, y;
    while (1) {
        printf("Enter row and column (1-3): ");
        scanf("%d %d", &x, &y);
        x--; y--;
        if (x >= 0 && x < SIZE && y >= 0 && y < SIZE && board[x][y] == ' ') {
            board[x][y] = 'X';
            break;
        }
        printf("Invalid move! Try again.\n");
    }
}

void aiMove() {
    int x, y;
    if (difficulty > 2) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';
                    if (checkWin('O')) return;
                    board[i][j] = ' ';
                }
            }
        }
    }
    do {
        x = rand() % SIZE;
        y = rand() % SIZE;
    } while (board[x][y] != ' ');
    board[x][y] = 'O';
}

void playGame() {
    initializeBoard();
    printBoard();
    while (1) {
        playerMove();
        printBoard();
        if (checkWin('X')) {
            printf("You win!\n");
            difficulty++;
            break;
        }
        if (isFull()) {
            printf("It's a draw!\n");
            break;
        }
        aiMove();
        printBoard();
        if (checkWin('O')) {
            printf("AI wins!\n");
            difficulty = difficulty > 1 ? difficulty - 1 : 1;
            break;
        }
        if (isFull()) {
            printf("It's a draw!\n");
            break;
        }
    }
}

int main() {
    srand(time(NULL));
    char playAgain;
    do {
        playGame();
        printf("Play again? (y/n): ");
        scanf(" %c", &playAgain);
    } while (playAgain == 'y');
    printf("Thanks for playing!\n");
    return 0;
}

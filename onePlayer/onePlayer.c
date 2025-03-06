#include <stdio.h>
#include "minimaxAgent.c"

int main(void) {
    char gameBoard[ROWS][COLS] = {
        {'-', '-', '-', '-', '-', '-'}, 
        {'-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-'}
    };
    char player;
    char turn = YELLOW;
    int lastCol, lastRow;
    bool flag = false;
    lastCol = -1;
    lastRow = -1;

    do {
        printf("Enter player (R/Y): ");
        scanf("%c", &player);
    } while(player != 'R' && player != 'Y');

    for(int t = 0; t<36 && !flag; t++) {
        printBoard(gameBoard);
        switchTurn(&turn);
        if(turn == player) {
            lastCol = getInput(gameBoard, player);
        }
        else {
            lastCol = getComputerInput(gameBoard, turn, lastRow, lastCol);
        }
        lastRow = insertPiece(gameBoard, lastCol, turn);
        flag = checkWinner(gameBoard, lastRow, lastCol);
    }

    if(flag) {
        if(turn == player) {
            printf("Player wins!\n");
            printf("Final board: \n");
        }
        else {
            printf("Computer wins!\n");
            printf("Final board: \n");
        }
    }
    else {
        printf("It's a tie\n");
        printf("Final board: \n");
    }

    printBoard(gameBoard);

    /*
    printBoard(gameBoard);
    columnEntered = getInput(gameBoard, turn);
    insertPiece(gameBoard, columnEntered, turn);
    printBoard(gameBoard);
    switchTurn(&turn);
    isConnect4 = checkOneDirection(gameBoard, 5, 2, -1, 1);
    printf("%c, %d", turn, isConnect4);
    */
}


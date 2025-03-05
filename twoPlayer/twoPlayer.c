#include <stdio.h>
#include "/workspaces/Connect4/configureBoard.c"

int main(void) {
    char gameBoard[ROWS][COLS] = {
        {'-', '-', '-', '-', '-', '-'}, 
        {'-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-'}
    };
    char turn = YELLOW;
    int lastCol, lastRow;
    bool flag = false;

    for(int t = 0; t<36 && !flag; t++) {
        printBoard(gameBoard);
        switchTurn(&turn);
        lastCol = getInput(gameBoard, turn);
        lastRow = insertPiece(gameBoard, lastCol, turn);
        flag = checkWinner(gameBoard, lastRow, lastCol);
    }

    if(flag) {
        if(turn == RED) {
            printf("Red wins!\n");
            printf("Final board: \n");
        }
        else {
            printf("Yellow wins!\n");
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


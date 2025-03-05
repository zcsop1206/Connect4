#include <stdio.h>
#include <stdbool.h>
#define ROWS 6
#define COLS 6
#define EMPTY '-'
#define RED 'R'
#define YELLOW 'Y'

void printBoard(char gameBoard[][COLS]);
/*
Prints array of cells 
Each cell is represented by
a dash (-) if EMPTY, 
character R if RED piece,
and character Y if YELLOW piece.
Need to consider printing higher index rows at the top 
and lower index rows at the bottom
Each row is printed on a separate line, i.e. after each row printed you should print a new line character. 
The size of the 2D array is known to be 6 by 6
*/

int getInput(char gameBoard[][COLS], char turn);
/*
Prompts the player whose turn is stored in turn to enter a valid column number:
ensures it is within bounds and not full.
*/

int insertPiece(char gameBoard[][COLS], int columnEntered, char turn);
/*
Inserts the piece of the player whose turn is stored in turn into the column columnEntered of the gameBoard.
Edit the gameBoard by making the piece fall to the lowest index available row in the chosen column.
returns row piece falls to.
*/

void switchTurn(char* turn);
/*
Switches the turn of the player stored in what turn points to. 
If the *turn is R, it should change it to Y and vice versa.
*/

bool checkOneDirection(char gameBoard[][COLS], int row, int col, int rowDir, int colDir);
/* 
Input row and col indices of a cell in the gameBoard and two integers rowDir and colDir representing the direction to check. 
For example, if (rowDir, colDir) is (+1, +1), it should check four pieces in the upward right direction. 
It returns true if there are four connected pieces in the given direction starting from the cell at row and col indices. Otherwise, it returns false.
*/

bool checkWinner(char gameBoard[][COLS], int lastRow, int lastCol);
/*
Checks if there is a winner in the current state of the gameBoard. 
It should call the checkOneDirection function for all possible directions (up/down, left/right, and diagonals) from each cell in the gameBoard. 
If any of the calls to checkOneDirection return true, the function should return true. Otherwise, it should return false.
*/

void printBoard(char gameBoard[][COLS]){
    for(int r=0; r<ROWS; r++) {
        for(int c=0; c<COLS; c++) {
            if(gameBoard[r][c]==EMPTY) {
                printf("-");
            }
            else if(gameBoard[r][c]==RED) {
                printf("R");
            }
            else {
                printf("Y");
            }
        }
        printf("\n");
    }
}

int getInput(char gameBoard[][COLS], char turn) {
    int chosenColumn;
    do {
        if(turn==RED) {
            printf("Red, ");
        }
        else {
            printf("Yellow, ");
        }
        printf("please enter a valid column number (0-5): ");
        scanf("%d", &chosenColumn);
    }while(chosenColumn<0 || chosenColumn>COLS-1 || gameBoard[0][chosenColumn]!='-');
    return chosenColumn;
}

int insertPiece(char gameBoard[][COLS], int columnEntered, char turn) {
    bool flag = true;
    int lastRow;
    for(int r = ROWS-1; flag; r--) {
        if(gameBoard[r][columnEntered]=='-') {
            gameBoard[r][columnEntered]=turn;
            lastRow = r;
            flag = false;
        }
    }
    return lastRow; 
}

void switchTurn(char* turn) {
    if(*turn == RED) {
        *turn = YELLOW;
    }
    else {
        *turn = RED;
    }
}

bool checkOneDirection(char gameBoard[][COLS], int row, int col, int rowDir, int colDir) {
    char piece = gameBoard[row][col];
    bool flag = true;
    for(int p=1; p<4; p++) {
        if(gameBoard[row+rowDir*p][col+colDir*p]!=piece) {
            flag = false;
            return flag;
        }
    }
    return flag;
}

bool checkWinner(char gameBoard[][COLS], int lastRow, int lastCol) {
    bool flag = false;
    if(lastRow>2) {
        flag = flag||checkOneDirection(gameBoard, lastRow, lastCol, -1, 0);
        if(lastCol<3) {
            flag = flag||checkOneDirection(gameBoard, lastRow, lastCol, -1, 1)||checkOneDirection(gameBoard, lastRow, lastCol, 0, 1);
        }
        else {
            flag = flag||checkOneDirection(gameBoard, lastRow, lastCol, -1, -1)||checkOneDirection(gameBoard, lastRow, lastCol, 0, -1);
        }
    }
    else {
        flag = flag||checkOneDirection(gameBoard, lastRow, lastCol, 1, 0);
        if(lastCol<3) {
            flag = flag||checkOneDirection(gameBoard, lastRow, lastCol, 1, 1)||checkOneDirection(gameBoard, lastRow, lastCol, 0, 1);
        }
        else {
            flag = flag||checkOneDirection(gameBoard, lastRow, lastCol, 1, -1)||checkOneDirection(gameBoard, lastRow, lastCol, 0, -1);
        }
    }
    return flag;
}